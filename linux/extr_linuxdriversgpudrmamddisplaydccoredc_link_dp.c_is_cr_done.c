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
struct TYPE_2__ {int /*<<< orphan*/  CR_DONE_0; } ;
union lane_status {TYPE_1__ bits; } ;
typedef  size_t uint32_t ;
typedef  enum dc_lane_count { ____Placeholder_dc_lane_count } dc_lane_count ;

/* Variables and functions */

__attribute__((used)) static bool is_cr_done(enum dc_lane_count ln_count,
	union lane_status *dpcd_lane_status)
{
	bool done = true;
	uint32_t lane;
	/*LANEx_CR_DONE bits All 1's?*/
	for (lane = 0; lane < (uint32_t)(ln_count); lane++) {
		if (!dpcd_lane_status[lane].bits.CR_DONE_0)
			done = false;
	}
	return done;

}