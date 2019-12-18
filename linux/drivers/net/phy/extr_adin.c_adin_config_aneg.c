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

/* Variables and functions */
 int adin_config_mdix (struct phy_device*) ; 
 int genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int adin_config_aneg(struct phy_device *phydev)
{
	int ret;

	ret = adin_config_mdix(phydev);
	if (ret)
		return ret;

	return genphy_config_aneg(phydev);
}