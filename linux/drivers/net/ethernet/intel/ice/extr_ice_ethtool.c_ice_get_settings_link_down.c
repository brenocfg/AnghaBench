#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ice_phy_type_to_ethtool (struct net_device*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static void
ice_get_settings_link_down(struct ethtool_link_ksettings *ks,
			   struct net_device *netdev)
{
	/* link is down and the driver needs to fall back on
	 * supported PHY types to figure out what info to display
	 */
	ice_phy_type_to_ethtool(netdev, ks);

	/* With no link, speed and duplex are unknown */
	ks->base.speed = SPEED_UNKNOWN;
	ks->base.duplex = DUPLEX_UNKNOWN;
}