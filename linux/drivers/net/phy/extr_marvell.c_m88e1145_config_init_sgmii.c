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
 int /*<<< orphan*/  MII_M1111_HWCFG_FIBER_COPPER_AUTO ; 
 int /*<<< orphan*/  MII_M1111_HWCFG_MODE_SGMII_NO_CLK ; 
 int m88e1111_config_init_hwcfg_mode (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88e1145_config_init_sgmii(struct phy_device *phydev)
{
	return m88e1111_config_init_hwcfg_mode(
		phydev, MII_M1111_HWCFG_MODE_SGMII_NO_CLK,
		MII_M1111_HWCFG_FIBER_COPPER_AUTO);
}