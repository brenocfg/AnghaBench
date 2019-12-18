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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  XWAY_MDIO_IMASK ; 
 int /*<<< orphan*/  XWAY_MDIO_ISTAT ; 
 int /*<<< orphan*/  XWAY_MMD_LED0H ; 
 int /*<<< orphan*/  XWAY_MMD_LED0L ; 
 int /*<<< orphan*/  XWAY_MMD_LED1H ; 
 int /*<<< orphan*/  XWAY_MMD_LED1L ; 
 int /*<<< orphan*/  XWAY_MMD_LED2H ; 
 int /*<<< orphan*/  XWAY_MMD_LED2L ; 
 int /*<<< orphan*/  XWAY_MMD_LEDCH ; 
 int XWAY_MMD_LEDCH_CBLINK_NONE ; 
 int XWAY_MMD_LEDCH_FBF_F16HZ ; 
 int XWAY_MMD_LEDCH_NACS_NONE ; 
 int XWAY_MMD_LEDCH_SBF_F02HZ ; 
 int XWAY_MMD_LEDCH_SCAN_NONE ; 
 int /*<<< orphan*/  XWAY_MMD_LEDCL ; 
 int XWAY_MMD_LEDxH_BLINKF_NONE ; 
 int XWAY_MMD_LEDxH_CON_LINK10XX ; 
 int XWAY_MMD_LEDxL_BLINKS_NONE ; 
 int XWAY_MMD_LEDxL_PULSE_RXACT ; 
 int XWAY_MMD_LEDxL_PULSE_TXACT ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xway_gphy_config_init(struct phy_device *phydev)
{
	int err;
	u32 ledxh;
	u32 ledxl;

	/* Mask all interrupts */
	err = phy_write(phydev, XWAY_MDIO_IMASK, 0);
	if (err)
		return err;

	/* Clear all pending interrupts */
	phy_read(phydev, XWAY_MDIO_ISTAT);

	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LEDCH,
		      XWAY_MMD_LEDCH_NACS_NONE |
		      XWAY_MMD_LEDCH_SBF_F02HZ |
		      XWAY_MMD_LEDCH_FBF_F16HZ);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LEDCL,
		      XWAY_MMD_LEDCH_CBLINK_NONE |
		      XWAY_MMD_LEDCH_SCAN_NONE);

	/**
	 * In most cases only one LED is connected to this phy, so
	 * configure them all to constant on and pulse mode. LED3 is
	 * only available in some packages, leave it in its reset
	 * configuration.
	 */
	ledxh = XWAY_MMD_LEDxH_BLINKF_NONE | XWAY_MMD_LEDxH_CON_LINK10XX;
	ledxl = XWAY_MMD_LEDxL_PULSE_TXACT | XWAY_MMD_LEDxL_PULSE_RXACT |
		XWAY_MMD_LEDxL_BLINKS_NONE;
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED0H, ledxh);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED0L, ledxl);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED1H, ledxh);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED1L, ledxl);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED2H, ledxh);
	phy_write_mmd(phydev, MDIO_MMD_VEND2, XWAY_MMD_LED2L, ledxl);

	return 0;
}