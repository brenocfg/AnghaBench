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
 int HDMI_8x60_PHY_REG2_PD_DESER ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_1 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_2 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_3 ; 
 int HDMI_8x60_PHY_REG2_PD_DRIVE_4 ; 
 int HDMI_8x60_PHY_REG2_PD_PLL ; 
 int HDMI_8x60_PHY_REG2_PD_PWRGEN ; 
 int HDMI_8x60_PHY_REG2_RCV_SENSE_EN ; 
 int HDMI_PHY_CTRL_SW_RESET ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG2 ; 
 int /*<<< orphan*/  REG_HDMI_8x60_PHY_REG3 ; 
 int /*<<< orphan*/  REG_HDMI_PHY_CTRL ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void hdmi_phy_8x60_powerdown(struct hdmi_phy *phy)
{
	/* Assert RESET PHY from controller */
	hdmi_phy_write(phy, REG_HDMI_PHY_CTRL,
		       HDMI_PHY_CTRL_SW_RESET);
	udelay(10);
	/* De-assert RESET PHY from controller */
	hdmi_phy_write(phy, REG_HDMI_PHY_CTRL, 0);
	/* Turn off Driver */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);
	udelay(10);
	/* Disable PLL */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG3, 0);
	/* Power down PHY, but keep RX-sense: */
	hdmi_phy_write(phy, REG_HDMI_8x60_PHY_REG2,
		       HDMI_8x60_PHY_REG2_RCV_SENSE_EN |
		       HDMI_8x60_PHY_REG2_PD_PWRGEN |
		       HDMI_8x60_PHY_REG2_PD_PLL |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_4 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_3 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_2 |
		       HDMI_8x60_PHY_REG2_PD_DRIVE_1 |
		       HDMI_8x60_PHY_REG2_PD_DESER);
}