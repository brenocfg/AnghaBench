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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_GMII 133 
#define  PHY_INTERFACE_MODE_MII 132 
#define  PHY_INTERFACE_MODE_RGMII 131 
#define  PHY_INTERFACE_MODE_RGMII_ID 130 
#define  PHY_INTERFACE_MODE_RMII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 int /*<<< orphan*/  SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII ; 
 int /*<<< orphan*/  SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RGMII ; 
 int /*<<< orphan*/  SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RMII ; 

__attribute__((used)) static int socfpga_set_phy_mode_common(int phymode, u32 *val)
{
	switch (phymode) {
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RGMII;
		break;
	case PHY_INTERFACE_MODE_MII:
	case PHY_INTERFACE_MODE_GMII:
	case PHY_INTERFACE_MODE_SGMII:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_GMII_MII;
		break;
	case PHY_INTERFACE_MODE_RMII:
		*val = SYSMGR_EMACGRP_CTRL_PHYSEL_ENUM_RMII;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}