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
struct phy_device {scalar_t__ state; scalar_t__ link; scalar_t__ loopback_enabled; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ PHY_NOLINK ; 
 scalar_t__ PHY_RUNNING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_link_down (struct phy_device*,int) ; 
 int /*<<< orphan*/  phy_link_up (struct phy_device*) ; 
 int phy_read_status (struct phy_device*) ; 

__attribute__((used)) static int phy_check_link_status(struct phy_device *phydev)
{
	int err;

	WARN_ON(!mutex_is_locked(&phydev->lock));

	/* Keep previous state if loopback is enabled because some PHYs
	 * report that Link is Down when loopback is enabled.
	 */
	if (phydev->loopback_enabled)
		return 0;

	err = phy_read_status(phydev);
	if (err)
		return err;

	if (phydev->link && phydev->state != PHY_RUNNING) {
		phydev->state = PHY_RUNNING;
		phy_link_up(phydev);
	} else if (!phydev->link && phydev->state != PHY_NOLINK) {
		phydev->state = PHY_NOLINK;
		phy_link_down(phydev, true);
	}

	return 0;
}