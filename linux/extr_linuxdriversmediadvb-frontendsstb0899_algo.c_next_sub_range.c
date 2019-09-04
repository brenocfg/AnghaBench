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
struct stb0899_params {scalar_t__ freq; } ;
struct stb0899_internal {int sub_dir; long sub_range; int srch_range; int tuner_offst; scalar_t__ freq; } ;
struct stb0899_state {struct stb0899_params params; struct stb0899_internal internal; } ;

/* Variables and functions */
 long min (int,int) ; 

__attribute__((used)) static void next_sub_range(struct stb0899_state *state)
{
	struct stb0899_internal *internal = &state->internal;
	struct stb0899_params *params = &state->params;

	long old_sub_range;

	if (internal->sub_dir > 0) {
		old_sub_range = internal->sub_range;
		internal->sub_range = min((internal->srch_range / 2) -
					  (internal->tuner_offst + internal->sub_range / 2),
					   internal->sub_range);

		if (internal->sub_range < 0)
			internal->sub_range = 0;

		internal->tuner_offst += (old_sub_range + internal->sub_range) / 2;
	}

	internal->freq = params->freq + (internal->sub_dir * internal->tuner_offst) / 1000;
	internal->sub_dir = -internal->sub_dir;
}