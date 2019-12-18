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
struct hdmi_phy {int dummy; } ;

/* Variables and functions */
 int HDMI_8x60_PHY_REG0_DESER_DEL_CTRL (int) ; 
 int HDMI_8x60_PHY_REG12_FORCE_LOCK ; 
 int HDMI_8x60_PHY_REG12_PLL_LOCK_DETECT_EN ; 
 int HDMI_8x60_PHY_REG12_RETIMING_EN ; 
 int HDMI_8x60_PHY_REG1_DTEST_MUX_SEL (int) ; 
 int HDMI_8x60_PHY_REG1_OUTVOL_SWING_CTRL (int) ; 
 int HDMI_8x60_PHY_REG2_PD_DESER ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_1 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_2 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_3 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_4 ; 
 int HDMI_8x60_PHY_REG2_PD_PLL ; 
 int HDMI_8x60_PHY_REG2_PD_PWRGEN ; 
 int HDMI_8x60_PHY_REG2_RCV_SENSE_EN ; 
 int HDMI_8x60_PHY_REG3_PLL_ENABLE ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG0 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG1 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG10 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG11 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG12 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG2 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG3 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG4 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG5 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG6 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG7 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG8 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG9 ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_phy_8x60_powerup(struct hdmi_phy *phy,
		unsigned long int pixclock)
{
	/* De-serializer delay D/C for non-lbk mode: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG0,
		       HDMI_8x60_PHY_REG0_DESER_DEL_CTRL(3));

	if (pixclock == 27000000) {
		/* video_format == HDMI_VFRMT_720x480p60_16_9 */
		hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG1,
			       HDMI_8x60_PHY_REG1_DTEST_MUX_SEL(5) |
			       HDMI_8x60_PHY_REG1_OUTVOL_SWING_CTRL(3));
	} else {
		hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG1,
			       HDMI_8x60_PHY_REG1_DTEST_MUX_SEL(5) |
			       HDMI_8x60_PHY_REG1_OUTVOL_SWING_CTRL(4));
	}

	/* No matter what, start from the power down mode: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_PWRGEN |
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Turn PowerGen on: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Turn PLL power on: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* Write to HIGH after PLL power down de-assert: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG3,
		       HDMI_8x60_PHY_REG3_PLL_ENABLE);

	/* ASIC power on; PHY REG9 = 0 */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG9, 0);

	/* Enable PLL lock detect, PLL lock det will go high after lock
	 * Enable the re-time logic
	 */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG12,
		       HDMI_8x60_PHY_REG12_RETIMING_EN |
		       HDMI_8x60_PHY_REG12_PLL_LOCK_DETECT_EN);

	/* Drivers are on: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DESER);

	/* If the RX detector is needed: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_RCV_SENSE_EN |
		       HDMI_8x60_PHY_REG2_PD_DESER);

	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG4, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG5, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG6, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG7, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG8, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG9, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG10, 0);
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG11, 0);

	/* If we want to use lock enable based on counting: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG12,
		       HDMI_8x60_PHY_REG12_RETIMING_EN |
		       HDMI_8x60_PHY_REG12_PLL_LOCK_DETECT_EN |
		       HDMI_8x60_PHY_REG12_FORCE_LOCK);
}