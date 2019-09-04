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
struct timing_generator {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_counter_moving ) (struct timing_generator*) ;} ;

/* Variables and functions */
 scalar_t__ dce120_timing_generator_is_in_vertical_blank (struct timing_generator*) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*) ; 

void dce120_timing_generator_wait_for_vblank(struct timing_generator *tg)
{
	/* We want to catch beginning of VBlank here, so if the first try are
	 * in VBlank, we might be very close to Active, in this case wait for
	 * another frame
	 */
	while (dce120_timing_generator_is_in_vertical_blank(tg)) {
		if (!tg->funcs->is_counter_moving(tg)) {
			/* error - no point to wait if counter is not moving */
			break;
		}
	}

	while (!dce120_timing_generator_is_in_vertical_blank(tg)) {
		if (!tg->funcs->is_counter_moving(tg)) {
			/* error - no point to wait if counter is not moving */
			break;
		}
	}
}