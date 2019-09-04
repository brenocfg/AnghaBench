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
struct hdmi_phy {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*,...) ; 
 int HDMI_PLL_POLL_MAX_READS ; 
 unsigned long HDMI_PLL_POLL_TIMEOUT_US ; 
 int /*<<< orphan*/  REG_HDMI_8996_PHY_STATUS ; 
 int hdmi_phy_read (struct hdmi_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (unsigned long) ; 

__attribute__((used)) static int hdmi_8996_phy_ready_status(struct hdmi_phy *phy)
{
	u32 nb_tries = HDMI_PLL_POLL_MAX_READS;
	unsigned long timeout = HDMI_PLL_POLL_TIMEOUT_US;
	u32 status;
	int phy_ready = 0;

	DBG("Waiting for PHY ready");

	while (nb_tries--) {
		status = hdmi_phy_read(phy, REG_HDMI_8996_PHY_STATUS);
		phy_ready = status & BIT(0);

		if (phy_ready)
			break;

		udelay(timeout);
	}

	DBG("PHY is %sready", phy_ready ? "" : "*not* ");

	return phy_ready;
}