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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ duplex; scalar_t__ port; scalar_t__ autoneg; int speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct de_private {int media_supported; int media_type; unsigned int media_lock; int media_advertise; int /*<<< orphan*/  dev; int /*<<< orphan*/  media_timer; scalar_t__ de21040; } ;

/* Variables and functions */
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_AUI ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_BNC ; 
 int ADVERTISED_TP ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int DE_MEDIA_AUI ; 
 int DE_MEDIA_BNC ; 
 int DE_MEDIA_TP ; 
 int DE_MEDIA_TP_AUTO ; 
 int DE_MEDIA_TP_FD ; 
 scalar_t__ DE_TIMER_NO_LINK ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
#define  PORT_AUI 129 
#define  PORT_BNC 128 
 scalar_t__ PORT_TP ; 
 int /*<<< orphan*/  de_link_down (struct de_private*) ; 
 int /*<<< orphan*/  de_set_media (struct de_private*) ; 
 int /*<<< orphan*/  de_start_rxtx (struct de_private*) ; 
 int /*<<< orphan*/  de_stop_rxtx (struct de_private*) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __de_set_link_ksettings(struct de_private *de,
				   const struct ethtool_link_ksettings *cmd)
{
	u32 new_media;
	unsigned int media_lock;
	u8 duplex = cmd->base.duplex;
	u8 port = cmd->base.port;
	u8 autoneg = cmd->base.autoneg;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	if (cmd->base.speed != 10)
		return -EINVAL;
	if (duplex != DUPLEX_HALF && duplex != DUPLEX_FULL)
		return -EINVAL;
	if (port != PORT_TP && port != PORT_AUI && port != PORT_BNC)
		return -EINVAL;
	if (de->de21040 && port == PORT_BNC)
		return -EINVAL;
	if (autoneg != AUTONEG_DISABLE && autoneg != AUTONEG_ENABLE)
		return -EINVAL;
	if (advertising & ~de->media_supported)
		return -EINVAL;
	if (autoneg == AUTONEG_ENABLE &&
	    (!(advertising & ADVERTISED_Autoneg)))
		return -EINVAL;

	switch (port) {
	case PORT_AUI:
		new_media = DE_MEDIA_AUI;
		if (!(advertising & ADVERTISED_AUI))
			return -EINVAL;
		break;
	case PORT_BNC:
		new_media = DE_MEDIA_BNC;
		if (!(advertising & ADVERTISED_BNC))
			return -EINVAL;
		break;
	default:
		if (autoneg == AUTONEG_ENABLE)
			new_media = DE_MEDIA_TP_AUTO;
		else if (duplex == DUPLEX_FULL)
			new_media = DE_MEDIA_TP_FD;
		else
			new_media = DE_MEDIA_TP;
		if (!(advertising & ADVERTISED_TP))
			return -EINVAL;
		if (!(advertising & (ADVERTISED_10baseT_Full |
				     ADVERTISED_10baseT_Half)))
			return -EINVAL;
		break;
	}

	media_lock = (autoneg == AUTONEG_ENABLE) ? 0 : 1;

	if ((new_media == de->media_type) &&
	    (media_lock == de->media_lock) &&
	    (advertising == de->media_advertise))
		return 0; /* nothing to change */

	de_link_down(de);
	mod_timer(&de->media_timer, jiffies + DE_TIMER_NO_LINK);
	de_stop_rxtx(de);

	de->media_type = new_media;
	de->media_lock = media_lock;
	de->media_advertise = advertising;
	de_set_media(de);
	if (netif_running(de->dev))
		de_start_rxtx(de);

	return 0;
}