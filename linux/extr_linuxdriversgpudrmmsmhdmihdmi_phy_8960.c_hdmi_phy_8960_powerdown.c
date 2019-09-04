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
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  REG_HDMI_8960_PHY_REG2 ; 
 int /*<<< orphan*/  hdmi_phy_write (struct hdmi_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_phy_8960_powerdown(struct hdmi_phy *phy)
{
	DBG("");

	hdmi_phy_write(phy, REG_HDMI_8960_PHY_REG2, 0x7f);
}