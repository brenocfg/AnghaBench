#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pll; } ;
struct omap_hdmi {TYPE_1__ pll; int /*<<< orphan*/  wp; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHYPWRCMD_OFF ; 
 int /*<<< orphan*/  dss_mgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_pll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_power_off_core (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_wp_clear_irqenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_wp_set_phy_pwr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_wp_video_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_power_off_full(struct omap_hdmi *hdmi)
{
	hdmi_wp_clear_irqenable(&hdmi->wp, 0xffffffff);

	hdmi_wp_video_stop(&hdmi->wp);

	dss_mgr_disable(&hdmi->output);

	hdmi_wp_set_phy_pwr(&hdmi->wp, HDMI_PHYPWRCMD_OFF);

	dss_pll_disable(&hdmi->pll.pll);

	hdmi_power_off_core(hdmi);
}