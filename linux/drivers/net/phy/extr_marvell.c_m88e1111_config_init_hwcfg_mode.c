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
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int MII_M1111_HWCFG_FIBER_COPPER_AUTO ; 
 int MII_M1111_HWCFG_FIBER_COPPER_RES ; 
 int MII_M1111_HWCFG_MODE_MASK ; 
 int /*<<< orphan*/  MII_M1111_PHY_EXT_SR ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int m88e1111_config_init_hwcfg_mode(struct phy_device *phydev,
					   u16 mode,
					   int fibre_copper_auto)
{
	if (fibre_copper_auto)
		mode |= MII_M1111_HWCFG_FIBER_COPPER_AUTO;

	return phy_modify(phydev, MII_M1111_PHY_EXT_SR,
			  MII_M1111_HWCFG_MODE_MASK |
			  MII_M1111_HWCFG_FIBER_COPPER_AUTO |
			  MII_M1111_HWCFG_FIBER_COPPER_RES,
			  mode);
}