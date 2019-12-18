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

/* Variables and functions */
 int PHY_INTERFACE_MODE_RTBI ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int PHY_INTERFACE_MODE_TBI ; 

__attribute__((used)) static inline int emac_phy_gpcs(int phy_mode)
{
	return  phy_mode == PHY_INTERFACE_MODE_SGMII ||
		phy_mode == PHY_INTERFACE_MODE_TBI ||
		phy_mode == PHY_INTERFACE_MODE_RTBI;
}