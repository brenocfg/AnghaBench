#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct omap_overlay_manager {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pll; } ;
struct TYPE_4__ {struct omap_overlay_manager* manager; } ;
struct TYPE_6__ {TYPE_2__ pll; int /*<<< orphan*/  wp; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHYPWRCMD_OFF ; 
 int /*<<< orphan*/  dss_mgr_disable (struct omap_overlay_manager*) ; 
 int /*<<< orphan*/  dss_pll_disable (int /*<<< orphan*/ *) ; 
 TYPE_3__ hdmi ; 
 int /*<<< orphan*/  hdmi_power_off_core (struct omap_dss_device*) ; 
 int /*<<< orphan*/  hdmi_wp_clear_irqenable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdmi_wp_set_phy_pwr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_wp_video_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_power_off_full(struct omap_dss_device *dssdev)
{
	struct omap_overlay_manager *mgr = hdmi.output.manager;

	hdmi_wp_clear_irqenable(&hdmi.wp, 0xffffffff);

	dss_mgr_disable(mgr);

	hdmi_wp_video_stop(&hdmi.wp);

	hdmi_wp_set_phy_pwr(&hdmi.wp, HDMI_PHYPWRCMD_OFF);

	dss_pll_disable(&hdmi.pll.pll);

	hdmi_power_off_core(dssdev);
}