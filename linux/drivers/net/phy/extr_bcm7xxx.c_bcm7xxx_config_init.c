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
 int /*<<< orphan*/  MII_BCM7XXX_100TX_DISC ; 
 int /*<<< orphan*/  MII_BCM7XXX_100TX_FALSE_CAR ; 
 int MII_BCM7XXX_64CLK_MDIO ; 
 int /*<<< orphan*/  MII_BCM7XXX_AUX_MODE ; 
 int /*<<< orphan*/  MII_BCM7XXX_SHD_MODE_2 ; 
 int /*<<< orphan*/  MII_BCM7XXX_TEST ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_set_clr_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bcm7xxx_config_init(struct phy_device *phydev)
{
	int ret;

	/* Enable 64 clock MDIO */
	phy_write(phydev, MII_BCM7XXX_AUX_MODE, MII_BCM7XXX_64CLK_MDIO);
	phy_read(phydev, MII_BCM7XXX_AUX_MODE);

	/* set shadow mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST,
			MII_BCM7XXX_SHD_MODE_2, MII_BCM7XXX_SHD_MODE_2);
	if (ret < 0)
		return ret;

	/* set iddq_clkbias */
	phy_write(phydev, MII_BCM7XXX_100TX_DISC, 0x0F00);
	udelay(10);

	/* reset iddq_clkbias */
	phy_write(phydev, MII_BCM7XXX_100TX_DISC, 0x0C00);

	phy_write(phydev, MII_BCM7XXX_100TX_FALSE_CAR, 0x7555);

	/* reset shadow mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST, 0, MII_BCM7XXX_SHD_MODE_2);
	if (ret < 0)
		return ret;

	return 0;
}