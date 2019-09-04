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
struct TYPE_5__ {int fixed_active; int program_fixed; } ;
struct TYPE_4__ {int btr_active; int program_btr; scalar_t__ inserted_frame_duration_in_us; scalar_t__ frames_to_insert; scalar_t__ frame_counter; } ;
struct TYPE_6__ {int ramp_is_active; unsigned int ramp_current_frame_duration_in_ns; } ;
struct freesync_state {TYPE_2__ fixed_refresh; TYPE_1__ btr; scalar_t__ nominal_refresh_rate_in_micro_hz; TYPE_3__ static_ramp; } ;

/* Variables and functions */
 scalar_t__ div64_u64 (unsigned long long,scalar_t__) ; 

__attribute__((used)) static void reset_freesync_state_variables(struct freesync_state* state)
{
	state->static_ramp.ramp_is_active = false;
	if (state->nominal_refresh_rate_in_micro_hz)
		state->static_ramp.ramp_current_frame_duration_in_ns =
			((unsigned int) (div64_u64(
			(1000000000ULL * 1000000),
			state->nominal_refresh_rate_in_micro_hz)));

	state->btr.btr_active = false;
	state->btr.frame_counter = 0;
	state->btr.frames_to_insert = 0;
	state->btr.inserted_frame_duration_in_us = 0;
	state->btr.program_btr = false;

	state->fixed_refresh.fixed_active = false;
	state->fixed_refresh.program_fixed = false;
}