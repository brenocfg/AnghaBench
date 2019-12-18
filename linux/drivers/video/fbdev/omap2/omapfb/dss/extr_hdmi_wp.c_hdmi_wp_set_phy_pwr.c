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
struct hdmi_wp_data {int /*<<< orphan*/  base; } ;
typedef  enum hdmi_phy_pwr { ____Placeholder_hdmi_phy_pwr } hdmi_phy_pwr ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HDMI_WP_PWR_CTRL ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int hdmi_wait_for_bit_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

int hdmi_wp_set_phy_pwr(struct hdmi_wp_data *wp, enum hdmi_phy_pwr val)
{
	/* Return if already the state */
	if (REG_GET(wp->base, HDMI_WP_PWR_CTRL, 5, 4) == val)
		return 0;

	/* Command for power control of HDMI PHY */
	REG_FLD_MOD(wp->base, HDMI_WP_PWR_CTRL, val, 7, 6);

	/* Status of the power control of HDMI PHY */
	if (hdmi_wait_for_bit_change(wp->base, HDMI_WP_PWR_CTRL, 5, 4, val)
			!= val) {
		DSSERR("Failed to set PHY power mode to %d\n", val);
		return -ETIMEDOUT;
	}

	return 0;
}