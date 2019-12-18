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
struct omap_video_timings {int dummy; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  venc_lock; struct omap_video_timings timings; scalar_t__ wss_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  dispc_set_tv_pclk (int) ; 
 scalar_t__ memcmp (struct omap_video_timings*,struct omap_video_timings*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ venc ; 

__attribute__((used)) static void venc_set_timings(struct omap_dss_device *dssdev,
		struct omap_video_timings *timings)
{
	DSSDBG("venc_set_timings\n");

	mutex_lock(&venc.venc_lock);

	/* Reset WSS data when the TV standard changes. */
	if (memcmp(&venc.timings, timings, sizeof(*timings)))
		venc.wss_data = 0;

	venc.timings = *timings;

	dispc_set_tv_pclk(13500000);

	mutex_unlock(&venc.venc_lock);
}