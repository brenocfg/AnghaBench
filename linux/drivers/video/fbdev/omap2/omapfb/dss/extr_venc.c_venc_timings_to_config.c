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
struct venc_config {int dummy; } ;
struct omap_video_timings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct omap_video_timings*,int) ; 
 int /*<<< orphan*/  omap_dss_ntsc_timings ; 
 int /*<<< orphan*/  omap_dss_pal_timings ; 
 struct venc_config const venc_config_ntsc_trm ; 
 struct venc_config const venc_config_pal_trm ; 

__attribute__((used)) static const struct venc_config *venc_timings_to_config(
		struct omap_video_timings *timings)
{
	if (memcmp(&omap_dss_pal_timings, timings, sizeof(*timings)) == 0)
		return &venc_config_pal_trm;

	if (memcmp(&omap_dss_ntsc_timings, timings, sizeof(*timings)) == 0)
		return &venc_config_ntsc_trm;

	BUG();
	return NULL;
}