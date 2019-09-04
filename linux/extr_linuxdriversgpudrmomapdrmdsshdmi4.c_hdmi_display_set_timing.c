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
struct videomode {int /*<<< orphan*/  pixelclock; } ;
struct TYPE_3__ {struct videomode vm; } ;
struct omap_hdmi {int /*<<< orphan*/  lock; TYPE_2__* dss; TYPE_1__ cfg; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dispc_set_tv_pclk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_display_set_timing(struct omap_dss_device *dssdev,
				    struct videomode *vm)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	mutex_lock(&hdmi->lock);

	hdmi->cfg.vm = *vm;

	dispc_set_tv_pclk(hdmi->dss->dispc, vm->pixelclock);

	mutex_unlock(&hdmi->lock);
}