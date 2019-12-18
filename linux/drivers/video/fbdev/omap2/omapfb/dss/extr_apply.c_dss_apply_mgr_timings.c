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
struct omap_video_timings {int dummy; } ;
struct omap_overlay_manager {int dummy; } ;
struct mgr_priv_data {int extra_info_dirty; struct omap_video_timings timings; } ;

/* Variables and functions */
 struct mgr_priv_data* get_mgr_priv (struct omap_overlay_manager*) ; 

__attribute__((used)) static void dss_apply_mgr_timings(struct omap_overlay_manager *mgr,
		const struct omap_video_timings *timings)
{
	struct mgr_priv_data *mp = get_mgr_priv(mgr);

	mp->timings = *timings;
	mp->extra_info_dirty = true;
}