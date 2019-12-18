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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  lock; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int EIO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_check_link_status (struct phy_device*) ; 
 int phy_config_aneg (struct phy_device*) ; 
 scalar_t__ phy_is_started (struct phy_device*) ; 
 int /*<<< orphan*/  phy_sanitize_settings (struct phy_device*) ; 

int phy_start_aneg(struct phy_device *phydev)
{
	int err;

	if (!phydev->drv)
		return -EIO;

	mutex_lock(&phydev->lock);

	if (AUTONEG_DISABLE == phydev->autoneg)
		phy_sanitize_settings(phydev);

	err = phy_config_aneg(phydev);
	if (err < 0)
		goto out_unlock;

	if (phy_is_started(phydev))
		err = phy_check_link_status(phydev);
out_unlock:
	mutex_unlock(&phydev->lock);

	return err;
}