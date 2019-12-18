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
typedef  int phy_interface_t ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_GMAC_IDX ; 
 int MAC_XGMAC_IDX ; 
#define  PHY_INTERFACE_MODE_SGMII 129 
#define  PHY_INTERFACE_MODE_XGMII 128 

__attribute__((used)) static int hns_mac_get_mode(phy_interface_t phy_if)
{
	switch (phy_if) {
	case PHY_INTERFACE_MODE_SGMII:
		return MAC_GMAC_IDX;
	case PHY_INTERFACE_MODE_XGMII:
		return MAC_XGMAC_IDX;
	default:
		return -EINVAL;
	}
}