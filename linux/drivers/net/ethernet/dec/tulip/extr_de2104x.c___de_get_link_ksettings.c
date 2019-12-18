#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int speed; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  port; scalar_t__ phy_address; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct de_private {int media_type; scalar_t__ media_lock; int /*<<< orphan*/  media_advertise; int /*<<< orphan*/  media_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
#define  DE_MEDIA_AUI 129 
#define  DE_MEDIA_BNC 128 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int FullDuplex ; 
 int /*<<< orphan*/  MacMode ; 
 int /*<<< orphan*/  PORT_AUI ; 
 int /*<<< orphan*/  PORT_BNC ; 
 int /*<<< orphan*/  PORT_TP ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __de_get_link_ksettings(struct de_private *de,
				    struct ethtool_link_ksettings *cmd)
{
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						de->media_supported);
	cmd->base.phy_address = 0;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						de->media_advertise);

	switch (de->media_type) {
	case DE_MEDIA_AUI:
		cmd->base.port = PORT_AUI;
		break;
	case DE_MEDIA_BNC:
		cmd->base.port = PORT_BNC;
		break;
	default:
		cmd->base.port = PORT_TP;
		break;
	}

	cmd->base.speed = 10;

	if (dr32(MacMode) & FullDuplex)
		cmd->base.duplex = DUPLEX_FULL;
	else
		cmd->base.duplex = DUPLEX_HALF;

	if (de->media_lock)
		cmd->base.autoneg = AUTONEG_DISABLE;
	else
		cmd->base.autoneg = AUTONEG_ENABLE;

	/* ignore maxtxpkt, maxrxpkt for now */
}