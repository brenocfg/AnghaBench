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
struct phy_device {scalar_t__ interface; int speed; scalar_t__ link; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_10GKR ; 
 scalar_t__ PHY_INTERFACE_MODE_2500BASEX ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
#define  SPEED_10 132 
#define  SPEED_100 131 
#define  SPEED_1000 130 
#define  SPEED_10000 129 
#define  SPEED_2500 128 

__attribute__((used)) static void mv3310_update_interface(struct phy_device *phydev)
{
	if ((phydev->interface == PHY_INTERFACE_MODE_SGMII ||
	     phydev->interface == PHY_INTERFACE_MODE_2500BASEX ||
	     phydev->interface == PHY_INTERFACE_MODE_10GKR) && phydev->link) {
		/* The PHY automatically switches its serdes interface (and
		 * active PHYXS instance) between Cisco SGMII, 10GBase-KR and
		 * 2500BaseX modes according to the speed.  Florian suggests
		 * setting phydev->interface to communicate this to the MAC.
		 * Only do this if we are already in one of the above modes.
		 */
		switch (phydev->speed) {
		case SPEED_10000:
			phydev->interface = PHY_INTERFACE_MODE_10GKR;
			break;
		case SPEED_2500:
			phydev->interface = PHY_INTERFACE_MODE_2500BASEX;
			break;
		case SPEED_1000:
		case SPEED_100:
		case SPEED_10:
			phydev->interface = PHY_INTERFACE_MODE_SGMII;
			break;
		default:
			break;
		}
	}
}