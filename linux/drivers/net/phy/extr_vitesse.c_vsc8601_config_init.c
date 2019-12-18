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
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 int vsc8601_add_skew (struct phy_device*) ; 

__attribute__((used)) static int vsc8601_config_init(struct phy_device *phydev)
{
	int ret = 0;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID)
		ret = vsc8601_add_skew(phydev);

	if (ret < 0)
		return ret;

	return 0;
}