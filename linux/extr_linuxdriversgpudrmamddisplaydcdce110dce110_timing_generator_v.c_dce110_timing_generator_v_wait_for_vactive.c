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
struct timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce110_timing_generator_v_is_counter_moving (struct timing_generator*) ; 
 scalar_t__ dce110_timing_generator_v_is_in_vertical_blank (struct timing_generator*) ; 

__attribute__((used)) static void dce110_timing_generator_v_wait_for_vactive(struct timing_generator *tg)
{
	while (dce110_timing_generator_v_is_in_vertical_blank(tg)) {
		if (!dce110_timing_generator_v_is_counter_moving(tg)) {
			/* error - no point to wait if counter is not moving */
			break;
		}
	}
}