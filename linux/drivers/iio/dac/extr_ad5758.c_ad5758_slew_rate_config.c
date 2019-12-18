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
typedef  scalar_t__ u64 ;
struct ad5758_state {scalar_t__ slew_time; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 scalar_t__ AD5758_FULL_SCALE_MICRO ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ S64_MAX ; 
 scalar_t__ abs (scalar_t__) ; 
 int ad5758_find_closest_match (scalar_t__*,int,scalar_t__) ; 
 int ad5758_slew_rate_set (struct ad5758_state*,unsigned int,unsigned int) ; 
 scalar_t__* ad5758_sr_clk ; 
 scalar_t__* ad5758_sr_step ; 
 int /*<<< orphan*/  do_div (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ad5758_slew_rate_config(struct ad5758_state *st)
{
	unsigned int sr_clk_idx, sr_step_idx;
	int i, res;
	s64 diff_new, diff_old;
	u64 sr_step, calc_slew_time;

	sr_clk_idx = 0;
	sr_step_idx = 0;
	diff_old = S64_MAX;
	/*
	 * The slew time can be determined by using the formula:
	 * Slew Time = (Full Scale Out / (Step Size x Update Clk Freq))
	 * where Slew time is expressed in microseconds
	 * Given the desired slew time, the following algorithm determines the
	 * best match for the step size and the update clock frequency.
	 */
	for (i = 0; i < ARRAY_SIZE(ad5758_sr_clk); i++) {
		/*
		 * Go through each valid update clock freq and determine a raw
		 * value for the step size by using the formula:
		 * Step Size = Full Scale Out / (Update Clk Freq * Slew Time)
		 */
		sr_step = AD5758_FULL_SCALE_MICRO;
		do_div(sr_step, ad5758_sr_clk[i]);
		do_div(sr_step, st->slew_time);
		/*
		 * After a raw value for step size was determined, find the
		 * closest valid match
		 */
		res = ad5758_find_closest_match(ad5758_sr_step,
						ARRAY_SIZE(ad5758_sr_step),
						sr_step);
		/* Calculate the slew time */
		calc_slew_time = AD5758_FULL_SCALE_MICRO;
		do_div(calc_slew_time, ad5758_sr_step[res]);
		do_div(calc_slew_time, ad5758_sr_clk[i]);
		/*
		 * Determine with how many microseconds the calculated slew time
		 * is different from the desired slew time and store the diff
		 * for the next iteration
		 */
		diff_new = abs(st->slew_time - calc_slew_time);
		if (diff_new < diff_old) {
			diff_old = diff_new;
			sr_clk_idx = i;
			sr_step_idx = res;
		}
	}

	return ad5758_slew_rate_set(st, sr_clk_idx, sr_step_idx);
}