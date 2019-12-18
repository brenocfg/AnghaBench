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
struct phy_device {int dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM54810_EXP_BROADREACH_LRE_MISC_CTL ; 
 int BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN ; 
 int /*<<< orphan*/  BCM5482_SHD_LEDS1 ; 
 int BCM5482_SHD_LEDS1_LED1 (int /*<<< orphan*/ ) ; 
 int BCM5482_SHD_LEDS1_LED3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM54XX_SHD_RGMII_MODE ; 
 int /*<<< orphan*/  BCM_EXP_MULTICOLOR ; 
 int BCM_LED_MULTICOLOR_IN_PHASE ; 
 int /*<<< orphan*/  BCM_LED_MULTICOLOR_LINK_ACT ; 
 int /*<<< orphan*/  BCM_LED_SRC_MULTICOLOR1 ; 
 scalar_t__ BRCM_PHY_MODEL (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BCM54XX_ECR ; 
 int MII_BCM54XX_ECR_IM ; 
 int /*<<< orphan*/  MII_BCM54XX_IMR ; 
 int MII_BCM54XX_INT_DUPLEX ; 
 int MII_BCM54XX_INT_LINK ; 
 int MII_BCM54XX_INT_SPEED ; 
 int PHY_BRCM_AUTO_PWRDWN_ENABLE ; 
 int PHY_BRCM_CLEAR_RGMII_MODE ; 
 int PHY_BRCM_DIS_TXCRXC_NOENRGY ; 
 int PHY_BRCM_RX_REFCLK_UNUSED ; 
 scalar_t__ PHY_ID_BCM50610 ; 
 scalar_t__ PHY_ID_BCM50610M ; 
 scalar_t__ PHY_ID_BCM54210E ; 
 scalar_t__ PHY_ID_BCM54612E ; 
 scalar_t__ PHY_ID_BCM54810 ; 
 int bcm54210e_config_init (struct phy_device*) ; 
 int bcm54612e_config_init (struct phy_device*) ; 
 int /*<<< orphan*/  bcm54xx_adjust_rxrefclk (struct phy_device*) ; 
 int /*<<< orphan*/  bcm54xx_phydsp_config (struct phy_device*) ; 
 int bcm_phy_read_exp (struct phy_device*,int /*<<< orphan*/ ) ; 
 int bcm_phy_write_exp (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcm_phy_write_shadow (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm54xx_config_init(struct phy_device *phydev)
{
	int reg, err, val;

	reg = phy_read(phydev, MII_BCM54XX_ECR);
	if (reg < 0)
		return reg;

	/* Mask interrupts globally.  */
	reg |= MII_BCM54XX_ECR_IM;
	err = phy_write(phydev, MII_BCM54XX_ECR, reg);
	if (err < 0)
		return err;

	/* Unmask events we are interested in.  */
	reg = ~(MII_BCM54XX_INT_DUPLEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_LINK);
	err = phy_write(phydev, MII_BCM54XX_IMR, reg);
	if (err < 0)
		return err;

	if ((BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610 ||
	     BRCM_PHY_MODEL(phydev) == PHY_ID_BCM50610M) &&
	    (phydev->dev_flags & PHY_BRCM_CLEAR_RGMII_MODE))
		bcm_phy_write_shadow(phydev, BCM54XX_SHD_RGMII_MODE, 0);

	if ((phydev->dev_flags & PHY_BRCM_RX_REFCLK_UNUSED) ||
	    (phydev->dev_flags & PHY_BRCM_DIS_TXCRXC_NOENRGY) ||
	    (phydev->dev_flags & PHY_BRCM_AUTO_PWRDWN_ENABLE))
		bcm54xx_adjust_rxrefclk(phydev);

	if (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54210E) {
		err = bcm54210e_config_init(phydev);
		if (err)
			return err;
	} else if (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54612E) {
		err = bcm54612e_config_init(phydev);
		if (err)
			return err;
	} else if (BRCM_PHY_MODEL(phydev) == PHY_ID_BCM54810) {
		/* For BCM54810, we need to disable BroadR-Reach function */
		val = bcm_phy_read_exp(phydev,
				       BCM54810_EXP_BROADREACH_LRE_MISC_CTL);
		val &= ~BCM54810_EXP_BROADREACH_LRE_MISC_CTL_EN;
		err = bcm_phy_write_exp(phydev,
					BCM54810_EXP_BROADREACH_LRE_MISC_CTL,
					val);
		if (err < 0)
			return err;
	}

	bcm54xx_phydsp_config(phydev);

	/* Encode link speed into LED1 and LED3 pair (green/amber).
	 * Also flash these two LEDs on activity. This means configuring
	 * them for MULTICOLOR and encoding link/activity into them.
	 */
	val = BCM5482_SHD_LEDS1_LED1(BCM_LED_SRC_MULTICOLOR1) |
		BCM5482_SHD_LEDS1_LED3(BCM_LED_SRC_MULTICOLOR1);
	bcm_phy_write_shadow(phydev, BCM5482_SHD_LEDS1, val);

	val = BCM_LED_MULTICOLOR_IN_PHASE |
		BCM5482_SHD_LEDS1_LED1(BCM_LED_MULTICOLOR_LINK_ACT) |
		BCM5482_SHD_LEDS1_LED3(BCM_LED_MULTICOLOR_LINK_ACT);
	bcm_phy_write_exp(phydev, BCM_EXP_MULTICOLOR, val);

	return 0;
}