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
 int /*<<< orphan*/  BCM54810_SHD_CLK_CTL ; 
 int BCM54810_SHD_CLK_CTL_GTXCLK_EN ; 
 int MII_BCM54XX_AUXCTL_MISC_WREN ; 
 int /*<<< orphan*/  MII_BCM54XX_AUXCTL_SHDWSEL_MISC ; 
 int MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int bcm54xx_auxctl_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int bcm54xx_auxctl_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int bcm_phy_read_shadow (struct phy_device*,int /*<<< orphan*/ ) ; 
 int bcm_phy_write_shadow (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm54xx_config_clock_delay(struct phy_device *phydev)
{
	int rc, val;

	/* handling PHY's internal RX clock delay */
	val = bcm54xx_auxctl_read(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	val |= MII_BCM54XX_AUXCTL_MISC_WREN;
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		/* Disable RGMII RXC-RXD skew */
		val &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
	}
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
		/* Enable RGMII RXC-RXD skew */
		val |= MII_BCM54XX_AUXCTL_SHDWSEL_MISC_RGMII_SKEW_EN;
	}
	rc = bcm54xx_auxctl_write(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
				  val);
	if (rc < 0)
		return rc;

	/* handling PHY's internal TX clock delay */
	val = bcm_phy_read_shadow(phydev, BCM54810_SHD_CLK_CTL);
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID) {
		/* Disable internal TX clock delay */
		val &= ~BCM54810_SHD_CLK_CTL_GTXCLK_EN;
	}
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID) {
		/* Enable internal TX clock delay */
		val |= BCM54810_SHD_CLK_CTL_GTXCLK_EN;
	}
	rc = bcm_phy_write_shadow(phydev, BCM54810_SHD_CLK_CTL, val);
	if (rc < 0)
		return rc;

	return 0;
}