#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gradual_static_ramp {int ramp_direction_is_up; int ramp_is_active; unsigned int ramp_current_frame_duration_in_ns; } ;
struct core_freesync {TYPE_3__* map; } ;
struct TYPE_5__ {unsigned int nominal_refresh_rate_in_micro_hz; struct gradual_static_ramp static_ramp; } ;
struct TYPE_6__ {TYPE_2__ state; TYPE_1__* caps; } ;
struct TYPE_4__ {unsigned int min_refresh_in_micro_hz; } ;

/* Variables and functions */
 scalar_t__ div64_u64 (unsigned long long,unsigned int) ; 

__attribute__((used)) static void set_static_ramp_variables(struct core_freesync *core_freesync,
		unsigned int index, bool enable_static_screen)
{
	unsigned int frame_duration = 0;
	unsigned int nominal_refresh_rate = core_freesync->map[index].state.
			nominal_refresh_rate_in_micro_hz;
	unsigned int min_refresh_rate= core_freesync->map[index].caps->
			min_refresh_in_micro_hz;
	struct gradual_static_ramp *static_ramp_variables =
			&core_freesync->map[index].state.static_ramp;

	/* If we are ENABLING static screen, refresh rate should go DOWN.
	 * If we are DISABLING static screen, refresh rate should go UP.
	 */
	if (enable_static_screen)
		static_ramp_variables->ramp_direction_is_up = false;
	else
		static_ramp_variables->ramp_direction_is_up = true;

	/* If ramp is not active, set initial frame duration depending on
	 * whether we are enabling/disabling static screen mode. If the ramp is
	 * already active, ramp should continue in the opposite direction
	 * starting with the current frame duration
	 */
	if (!static_ramp_variables->ramp_is_active) {
		if (enable_static_screen == true) {
			/* Going to lower refresh rate, so start from max
			 * refresh rate (min frame duration)
			 */
			frame_duration = ((unsigned int) (div64_u64(
				(1000000000ULL * 1000000),
				nominal_refresh_rate)));
		} else {
			/* Going to higher refresh rate, so start from min
			 * refresh rate (max frame duration)
			 */
			frame_duration = ((unsigned int) (div64_u64(
				(1000000000ULL * 1000000),
				min_refresh_rate)));
		}
		static_ramp_variables->
			ramp_current_frame_duration_in_ns = frame_duration;

		static_ramp_variables->ramp_is_active = true;
	}
}