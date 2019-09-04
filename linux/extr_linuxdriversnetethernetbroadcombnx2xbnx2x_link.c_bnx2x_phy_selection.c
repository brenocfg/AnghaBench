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
typedef  int u32 ;
struct link_params {int multi_phy_config; } ;

/* Variables and functions */
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY 131 
#define  PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY 130 
 int PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT ; 
 int PORT_HW_CFG_PHY_SELECTION_MASK ; 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY 129 
#define  PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY 128 
 int PORT_HW_CFG_PHY_SWAPPED_ENABLED ; 

u32 bnx2x_phy_selection(struct link_params *params)
{
	u32 phy_config_swapped, prio_cfg;
	u32 return_cfg = PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT;

	phy_config_swapped = params->multi_phy_config &
		PORT_HW_CFG_PHY_SWAPPED_ENABLED;

	prio_cfg = params->multi_phy_config &
			PORT_HW_CFG_PHY_SELECTION_MASK;

	if (phy_config_swapped) {
		switch (prio_cfg) {
		case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
		     return_cfg = PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY;
		     break;
		case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
		     return_cfg = PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY;
		     break;
		case PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
		     return_cfg = PORT_HW_CFG_PHY_SELECTION_FIRST_PHY;
		     break;
		case PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
		     return_cfg = PORT_HW_CFG_PHY_SELECTION_SECOND_PHY;
		     break;
		}
	} else
		return_cfg = prio_cfg;

	return return_cfg;
}