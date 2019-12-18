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
struct at_state_t {int /*<<< orphan*/  timer_index; int /*<<< orphan*/  cs; scalar_t__ timer_expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_MCMD ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,struct at_state_t*,scalar_t__) ; 
 int /*<<< orphan*/  gigaset_add_event (int /*<<< orphan*/ ,struct at_state_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_timeout(struct at_state_t *at_state)
{
	if (!at_state->timer_expires)
		return 0;

	if (--at_state->timer_expires) {
		gig_dbg(DEBUG_MCMD, "decreased timer of %p to %lu",
			at_state, at_state->timer_expires);
		return 0;
	}

	gigaset_add_event(at_state->cs, at_state, EV_TIMEOUT, NULL,
			  at_state->timer_index, NULL);
	return 1;
}