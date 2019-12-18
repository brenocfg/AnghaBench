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
 int /*<<< orphan*/  AFE_HPF_TRIM_OTHERS ; 
 int /*<<< orphan*/  AFE_RXCONFIG_0 ; 
 int /*<<< orphan*/  AFE_RXCONFIG_1 ; 
 int /*<<< orphan*/  AFE_RX_LP_COUNTER ; 
 int /*<<< orphan*/  AFE_TX_CONFIG ; 
 int /*<<< orphan*/  DSP_TAP10 ; 
 int /*<<< orphan*/  MII_BRCM_CORE_BASE1E ; 
 int /*<<< orphan*/  PLL_PLLCTRL_1 ; 
 int /*<<< orphan*/  PLL_PLLCTRL_2 ; 
 int /*<<< orphan*/  PLL_PLLCTRL_4 ; 
 int /*<<< orphan*/  bcm_phy_r_rc_cal_reset (struct phy_device*) ; 
 int /*<<< orphan*/  bcm_phy_write_misc (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

int bcm_phy_28nm_a0b0_afe_config_init(struct phy_device *phydev)
{
	/* Increase VCO range to prevent unlocking problem of PLL at low
	 * temp
	 */
	bcm_phy_write_misc(phydev, PLL_PLLCTRL_1, 0x0048);

	/* Change Ki to 011 */
	bcm_phy_write_misc(phydev, PLL_PLLCTRL_2, 0x021b);

	/* Disable loading of TVCO buffer to bandgap, set bandgap trim
	 * to 111
	 */
	bcm_phy_write_misc(phydev, PLL_PLLCTRL_4, 0x0e20);

	/* Adjust bias current trim by -3 */
	bcm_phy_write_misc(phydev, DSP_TAP10, 0x690b);

	/* Switch to CORE_BASE1E */
	phy_write(phydev, MII_BRCM_CORE_BASE1E, 0xd);

	bcm_phy_r_rc_cal_reset(phydev);

	/* write AFE_RXCONFIG_0 */
	bcm_phy_write_misc(phydev, AFE_RXCONFIG_0, 0xeb19);

	/* write AFE_RXCONFIG_1 */
	bcm_phy_write_misc(phydev, AFE_RXCONFIG_1, 0x9a3f);

	/* write AFE_RX_LP_COUNTER */
	bcm_phy_write_misc(phydev, AFE_RX_LP_COUNTER, 0x7fc0);

	/* write AFE_HPF_TRIM_OTHERS */
	bcm_phy_write_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x000b);

	/* write AFTE_TX_CONFIG */
	bcm_phy_write_misc(phydev, AFE_TX_CONFIG, 0x0800);

	return 0;
}