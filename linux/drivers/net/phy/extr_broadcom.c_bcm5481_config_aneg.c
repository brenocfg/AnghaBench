#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct phy_device {TYPE_2__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ MII_BCM54XX_EXP_SEL_ER ; 
 int /*<<< orphan*/  bcm54xx_config_clock_delay (struct phy_device*) ; 
 int bcm_phy_write_exp (struct phy_device*,scalar_t__,int) ; 
 int genphy_config_aneg (struct phy_device*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

__attribute__((used)) static int bcm5481_config_aneg(struct phy_device *phydev)
{
	struct device_node *np = phydev->mdio.dev.of_node;
	int ret;

	/* Aneg firsly. */
	ret = genphy_config_aneg(phydev);

	/* Then we can set up the delay. */
	bcm54xx_config_clock_delay(phydev);

	if (of_property_read_bool(np, "enet-phy-lane-swap")) {
		/* Lane Swap - Undocumented register...magic! */
		ret = bcm_phy_write_exp(phydev, MII_BCM54XX_EXP_SEL_ER + 0x9,
					0x11B);
		if (ret < 0)
			return ret;
	}

	return ret;
}