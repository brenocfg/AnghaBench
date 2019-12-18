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
struct phy_device {int /*<<< orphan*/  attached_dev; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  phy_duplex_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_pause_str (struct phy_device*) ; 
 int /*<<< orphan*/  phy_speed_to_str (int /*<<< orphan*/ ) ; 

void phy_print_status(struct phy_device *phydev)
{
	if (phydev->link) {
		netdev_info(phydev->attached_dev,
			"Link is Up - %s/%s - flow control %s\n",
			phy_speed_to_str(phydev->speed),
			phy_duplex_to_str(phydev->duplex),
			phy_pause_str(phydev));
	} else	{
		netdev_info(phydev->attached_dev, "Link is Down\n");
	}
}