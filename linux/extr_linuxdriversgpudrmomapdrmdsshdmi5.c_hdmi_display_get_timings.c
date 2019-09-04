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
struct videomode {int dummy; } ;
struct TYPE_2__ {struct videomode vm; } ;
struct omap_hdmi {TYPE_1__ cfg; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 

__attribute__((used)) static void hdmi_display_get_timings(struct omap_dss_device *dssdev,
				     struct videomode *vm)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	*vm = hdmi->cfg.vm;
}