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
struct powerdomain {int state; int /*<<< orphan*/ * state_counter; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int OMAP_POWERSTATE_MASK ; 
 int PWRDM_POWER_RET ; 
#define  PWRDM_STATE_NOW 129 
#define  PWRDM_STATE_PREV 128 
 int PWRDM_TRACE_STATES_FLAG ; 
 int /*<<< orphan*/  _update_logic_membank_counters (struct powerdomain*) ; 
 int /*<<< orphan*/  pm_dbg_update_time (struct powerdomain*,int) ; 
 int pwrdm_read_next_pwrst (struct powerdomain*) ; 
 int pwrdm_read_prev_pwrst (struct powerdomain*) ; 
 int pwrdm_read_pwrst (struct powerdomain*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  trace_power_domain_target_rcuidle (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _pwrdm_state_switch(struct powerdomain *pwrdm, int flag)
{

	int prev, next, state, trace_state = 0;

	if (pwrdm == NULL)
		return -EINVAL;

	state = pwrdm_read_pwrst(pwrdm);

	switch (flag) {
	case PWRDM_STATE_NOW:
		prev = pwrdm->state;
		break;
	case PWRDM_STATE_PREV:
		prev = pwrdm_read_prev_pwrst(pwrdm);
		if (pwrdm->state != prev)
			pwrdm->state_counter[prev]++;
		if (prev == PWRDM_POWER_RET)
			_update_logic_membank_counters(pwrdm);
		/*
		 * If the power domain did not hit the desired state,
		 * generate a trace event with both the desired and hit states
		 */
		next = pwrdm_read_next_pwrst(pwrdm);
		if (next != prev) {
			trace_state = (PWRDM_TRACE_STATES_FLAG |
				       ((next & OMAP_POWERSTATE_MASK) << 8) |
				       ((prev & OMAP_POWERSTATE_MASK) << 0));
			trace_power_domain_target_rcuidle(pwrdm->name,
							  trace_state,
							  raw_smp_processor_id());
		}
		break;
	default:
		return -EINVAL;
	}

	if (state != prev)
		pwrdm->state_counter[state]++;

	pm_dbg_update_time(pwrdm, prev);

	pwrdm->state = state;

	return 0;
}