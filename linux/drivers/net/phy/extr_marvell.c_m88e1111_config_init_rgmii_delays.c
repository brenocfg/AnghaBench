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
 int /*<<< orphan*/  MII_M1111_PHY_EXT_CR ; 
 int MII_M1111_RGMII_RX_DELAY ; 
 int MII_M1111_RGMII_TX_DELAY ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int m88e1111_config_init_rgmii_delays(struct phy_device *phydev)
{
	int delay;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID) {
		delay = MII_M1111_RGMII_RX_DELAY | MII_M1111_RGMII_TX_DELAY;
	} else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
		delay = MII_M1111_RGMII_RX_DELAY;
	} else if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		delay = MII_M1111_RGMII_TX_DELAY;
	} else {
		delay = 0;
	}

	return phy_modify(phydev, MII_M1111_PHY_EXT_CR,
			  MII_M1111_RGMII_RX_DELAY | MII_M1111_RGMII_TX_DELAY,
			  delay);
}