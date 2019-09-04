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
 int /*<<< orphan*/  DBG (char*,unsigned long) ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG0 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG1 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG10 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG11 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG2 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG3 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG4 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG5 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG6 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG7 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG8 ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG9 ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_phy_8960_powerup(struct hdmi_phy *phy,
				  unsigned long int pixclock)
{
	DBG("pixclock: %lu", pixclock);

	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG0, 0x1b);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG1, 0xf2);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG4, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG5, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG6, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG7, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG8, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG9, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG10, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG11, 0x00);
	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG3, 0x20);
}