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
 int /*<<< orphan*/  MII_BCM54XX_AUX_CTL ; 
 int /*<<< orphan*/  MII_BRCM_CORE_BASE1E ; 
 int /*<<< orphan*/  MII_BRCM_CORE_EXPB0 ; 
 int /*<<< orphan*/  MII_BRCM_CORE_EXPB1 ; 
 int bcm_phy_write_exp_sel (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int bcm_phy_write_misc (struct phy_device*,int,int,int) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm_cygnus_afe_config(struct phy_device *phydev)
{
	int rc;

	/* ensure smdspclk is enabled */
	rc = phy_write(phydev, MII_BCM54XX_AUX_CTL, 0x0c30);
	if (rc < 0)
		return rc;

	/* AFE_VDAC_ICTRL_0 bit 7:4 Iq=1100 for 1g 10bt, normal modes */
	rc = bcm_phy_write_misc(phydev, 0x39, 0x01, 0xA7C8);
	if (rc < 0)
		return rc;

	/* AFE_HPF_TRIM_OTHERS bit11=1, short cascode enable for all modes*/
	rc = bcm_phy_write_misc(phydev, 0x3A, 0x00, 0x0803);
	if (rc < 0)
		return rc;

	/* AFE_TX_CONFIG_1 bit 7:4 Iq=1100 for test modes */
	rc = bcm_phy_write_misc(phydev, 0x3A, 0x01, 0xA740);
	if (rc < 0)
		return rc;

	/* AFE TEMPSEN_OTHERS rcal_HT, rcal_LT 10000 */
	rc = bcm_phy_write_misc(phydev, 0x3A, 0x03, 0x8400);
	if (rc < 0)
		return rc;

	/* AFE_FUTURE_RSV bit 2:0 rccal <2:0>=100 */
	rc = bcm_phy_write_misc(phydev, 0x3B, 0x00, 0x0004);
	if (rc < 0)
		return rc;

	/* Adjust bias current trim to overcome digital offSet */
	rc = phy_write(phydev, MII_BRCM_CORE_BASE1E, 0x02);
	if (rc < 0)
		return rc;

	/* make rcal=100, since rdb default is 000 */
	rc = bcm_phy_write_exp_sel(phydev, MII_BRCM_CORE_EXPB1, 0x10);
	if (rc < 0)
		return rc;

	/* CORE_EXPB0, Reset R_CAL/RC_CAL Engine */
	rc = bcm_phy_write_exp_sel(phydev, MII_BRCM_CORE_EXPB0, 0x10);
	if (rc < 0)
		return rc;

	/* CORE_EXPB0, Disable Reset R_CAL/RC_CAL Engine */
	rc = bcm_phy_write_exp_sel(phydev, MII_BRCM_CORE_EXPB0, 0x00);

	return 0;
}