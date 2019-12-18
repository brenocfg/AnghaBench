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
 int /*<<< orphan*/  AFE_RXCONFIG_1 ; 
 int /*<<< orphan*/  AFE_TX_CONFIG ; 
 int /*<<< orphan*/  AFE_VDCA_ICTRL_0 ; 
 int /*<<< orphan*/  DSP_TAP10 ; 
 int /*<<< orphan*/  MII_BRCM_CORE_BASE1E ; 
 int /*<<< orphan*/  bcm_phy_r_rc_cal_reset (struct phy_device*) ; 
 int /*<<< orphan*/  bcm_phy_write_misc (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm7xxx_28nm_e0_plus_afe_config_init(struct phy_device *phydev)
{
	/* AFE_RXCONFIG_1, provide more margin for INL/DNL measurement */
	bcm_phy_write_misc(phydev, AFE_RXCONFIG_1, 0x9b2f);

	/* AFE_TX_CONFIG, set 100BT Cfeed=011 to improve rise/fall time */
	bcm_phy_write_misc(phydev, AFE_TX_CONFIG, 0x431);

	/* AFE_VDCA_ICTRL_0, set Iq=1101 instead of 0111 for AB symmetry */
	bcm_phy_write_misc(phydev, AFE_VDCA_ICTRL_0, 0xa7da);

	/* AFE_HPF_TRIM_OTHERS, set 100Tx/10BT to -4.5% swing and set rCal
	 * offset for HT=0 code
	 */
	bcm_phy_write_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x00e3);

	/* CORE_BASE1E, force trim to overwrite and set I_ext trim to 0000 */
	phy_write(phydev, MII_BRCM_CORE_BASE1E, 0x0010);

	/* DSP_TAP10, adjust bias current trim (+0% swing, +0 tick) */
	bcm_phy_write_misc(phydev, DSP_TAP10, 0x011b);

	/* Reset R_CAL/RC_CAL engine */
	bcm_phy_r_rc_cal_reset(phydev);

	return 0;
}