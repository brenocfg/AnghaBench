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
struct csis_state {int /*<<< orphan*/  slock; TYPE_1__* events; int /*<<< orphan*/  sd; } ;
struct TYPE_2__ {scalar_t__ counter; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int S5PCSIS_NUM_EVENTS ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void s5pcsis_log_counters(struct csis_state *state, bool non_errors)
{
	int i = non_errors ? S5PCSIS_NUM_EVENTS : S5PCSIS_NUM_EVENTS - 4;
	unsigned long flags;

	spin_lock_irqsave(&state->slock, flags);

	for (i--; i >= 0; i--) {
		if (state->events[i].counter > 0 || debug)
			v4l2_info(&state->sd, "%s events: %d\n",
				  state->events[i].name,
				  state->events[i].counter);
	}
	spin_unlock_irqrestore(&state->slock, flags);
}