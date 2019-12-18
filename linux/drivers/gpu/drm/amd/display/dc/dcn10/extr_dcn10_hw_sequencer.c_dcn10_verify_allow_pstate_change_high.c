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
struct dc {TYPE_1__* res_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  hubbub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 scalar_t__ dcn10_hw_wa_force_recovery (struct dc*) ; 
 int /*<<< orphan*/  dcn10_log_hw_state (struct dc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hubbub1_verify_allow_pstate_change_high (int /*<<< orphan*/ ) ; 

void dcn10_verify_allow_pstate_change_high(struct dc *dc)
{
	static bool should_log_hw_state; /* prevent hw state log by default */

	if (!hubbub1_verify_allow_pstate_change_high(dc->res_pool->hubbub)) {
		if (should_log_hw_state) {
			dcn10_log_hw_state(dc, NULL);
		}
		BREAK_TO_DEBUGGER();
		if (dcn10_hw_wa_force_recovery(dc)) {
		/*check again*/
			if (!hubbub1_verify_allow_pstate_change_high(dc->res_pool->hubbub))
				BREAK_TO_DEBUGGER();
		}
	}
}