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
struct omap_video_timings {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_3__ {struct omap_video_timings timings; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 TYPE_2__ hdmi ; 

__attribute__((used)) static void hdmi_display_get_timings(struct omap_dss_device *dssdev,
		struct omap_video_timings *timings)
{
	*timings = hdmi.cfg.timings;
}