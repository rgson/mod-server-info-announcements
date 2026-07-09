/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>
 *               2026 Robin Gustafsson <robin@rgson.se>
 * released under GNU AGPL v3 license:
 * https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Chat.h"
#include "Config.h"
#include "GameTime.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "StringFormat.h"
#include "Util.h"

class ServerInfoAnnouncementsPlayer : public PlayerScript
{
public:
    ServerInfoAnnouncementsPlayer() : PlayerScript("ServerInfoAnnouncementsPlayer", {
        PLAYERHOOK_ON_LOGIN
    }) { }

    void OnPlayerLogin(Player* player) override
    {
        if (!sConfigMgr->GetOption<bool>("ServerInfoAnnouncements.Enable", false))
        {
            return;
        }

        if (sConfigMgr->GetOption<bool>("ServerInfoAnnouncements.ShowCurrentUptime", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage(
                Acore::StringFormat("Server uptime: {}", secsToTimeString(GameTime::GetUptime().count()))
            );
        }
    }
};

void AddServerInfoAnnouncementsScripts()
{
    new ServerInfoAnnouncementsPlayer();
}
