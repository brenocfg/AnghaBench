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
 int /*<<< orphan*/  AFE_RXCONFIG_2 ; 
 int /*<<< orphan*/  DSP_TAP10 ; 
 int /*<<< orphan*/  bcm_phy_r_rc_cal_reset (struct phy_device*) ; 
 int /*<<< orphan*/  bcm_phy_write_misc (struct phy_device*,int,int,...) ; 

__attribute__((used)) static int bcm7xxx_28nm_a0_patch_afe_config_init(struct phy_device *phydev)
{
	/* +1 RC_CAL codes for RL centering for both LT and HT conditions */
	bcm_phy_write_misc(phydev, AFE_RXCONFIG_2, 0xd003);

	/* Cut master bias current by 2% to compensate for RC_CAL offset */
	bcm_phy_write_misc(phydev, DSP_TAP10, 0x791b);

	/* Improve hybrid leakage */
	bcm_phy_write_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x10e3);

	/* Change rx_on_tune 8 to 0xf */
	bcm_phy_write_misc(phydev, 0x21, 0x2, 0x87f6);

	/* Change 100Tx EEE bandwidth */
	bcm_phy_write_misc(phydev, 0x22, 0x2, 0x017d);

	/* Enable ffe zero detection for Vitesse interoperability */
	bcm_phy_write_misc(phydev, 0x26, 0x2, 0x0015);

	bcm_phy_r_rc_cal_reset(phydev);

	return 0;
}