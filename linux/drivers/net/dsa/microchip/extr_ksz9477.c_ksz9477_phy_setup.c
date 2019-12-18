#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct phy_device {int dummy; } ;
struct ksz_device {int phy_port_cnt; int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Half_BIT ; 
 int GBIT_SUPPORT ; 
 int /*<<< orphan*/  phy_remove_link_mode (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz9477_phy_setup(struct ksz_device *dev, int port,
			      struct phy_device *phy)
{
	/* Only apply to port with PHY. */
	if (port >= dev->phy_port_cnt)
		return;

	/* The MAC actually cannot run in 1000 half-duplex mode. */
	phy_remove_link_mode(phy,
			     ETHTOOL_LINK_MODE_1000baseT_Half_BIT);

	/* PHY does not support gigabit. */
	if (!(dev->features & GBIT_SUPPORT))
		phy_remove_link_mode(phy,
				     ETHTOOL_LINK_MODE_1000baseT_Full_BIT);
}