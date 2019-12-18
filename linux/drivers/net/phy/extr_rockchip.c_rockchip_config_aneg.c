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
struct phy_device {int /*<<< orphan*/  mdix; } ;

/* Variables and functions */
 int genphy_config_aneg (struct phy_device*) ; 
 int rockchip_set_polarity (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_config_aneg(struct phy_device *phydev)
{
	int err;

	err = rockchip_set_polarity(phydev, phydev->mdix);
	if (err < 0)
		return err;

	return genphy_config_aneg(phydev);
}