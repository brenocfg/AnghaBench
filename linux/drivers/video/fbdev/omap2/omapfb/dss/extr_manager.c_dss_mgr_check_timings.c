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
struct omap_overlay_manager {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dispc_mgr_timings_ok (int /*<<< orphan*/ ,struct omap_video_timings const*) ; 

int dss_mgr_check_timings(struct omap_overlay_manager *mgr,
		const struct omap_video_timings *timings)
{
	if (!dispc_mgr_timings_ok(mgr->id, timings)) {
		DSSERR("check_manager: invalid timings\n");
		return -EINVAL;
	}

	return 0;
}