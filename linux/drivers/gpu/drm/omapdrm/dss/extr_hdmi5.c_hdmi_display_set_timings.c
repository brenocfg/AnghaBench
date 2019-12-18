#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vm; } ;
struct omap_hdmi {int /*<<< orphan*/  lock; TYPE_2__* dss; TYPE_1__ cfg; } ;
struct omap_dss_device {int dummy; } ;
struct drm_display_mode {int clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_set_tv_pclk (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_display_mode_to_videomode (struct drm_display_mode const*,int /*<<< orphan*/ *) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_display_set_timings(struct omap_dss_device *dssdev,
				     const struct drm_display_mode *mode)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	mutex_lock(&hdmi->lock);

	drm_display_mode_to_videomode(mode, &hdmi->cfg.vm);

	dispc_set_tv_pclk(hdmi->dss->dispc, mode->clock * 1000);

	mutex_unlock(&hdmi->lock);
}