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
struct omap_video_timings {int pixelclock; int x_res; int hfp; int hbp; int hsw; int y_res; int vfp; int vbp; int vsw; } ;
struct omap_dss_device {TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_timings ) (struct omap_dss_device*,struct omap_video_timings*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_dss_device*,struct omap_video_timings*) ; 

__attribute__((used)) static ssize_t display_timings_show(struct omap_dss_device *dssdev, char *buf)
{
	struct omap_video_timings t;

	if (!dssdev->driver->get_timings)
		return -ENOENT;

	dssdev->driver->get_timings(dssdev, &t);

	return snprintf(buf, PAGE_SIZE, "%u,%u/%u/%u/%u,%u/%u/%u/%u\n",
			t.pixelclock,
			t.x_res, t.hfp, t.hbp, t.hsw,
			t.y_res, t.vfp, t.vbp, t.vsw);
}