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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ BGX_MODE_QSGMII ; 
 scalar_t__ BGX_MODE_RGMII ; 
 int PHY_INTERFACE_MODE_QSGMII ; 
 int PHY_INTERFACE_MODE_RGMII ; 
 int PHY_INTERFACE_MODE_SGMII ; 

__attribute__((used)) static int phy_interface_mode(u8 lmac_type)
{
	if (lmac_type == BGX_MODE_QSGMII)
		return PHY_INTERFACE_MODE_QSGMII;
	if (lmac_type == BGX_MODE_RGMII)
		return PHY_INTERFACE_MODE_RGMII;

	return PHY_INTERFACE_MODE_SGMII;
}