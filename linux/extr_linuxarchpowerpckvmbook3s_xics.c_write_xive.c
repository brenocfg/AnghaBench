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
typedef  scalar_t__ u32 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {int /*<<< orphan*/  lock; } ;
struct ics_irq_state {scalar_t__ resend; scalar_t__ masked_pending; scalar_t__ saved_priority; scalar_t__ priority; scalar_t__ server; } ;

/* Variables and functions */
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static bool write_xive(struct kvmppc_xics *xics, struct kvmppc_ics *ics,
		       struct ics_irq_state *state,
		       u32 server, u32 priority, u32 saved_priority)
{
	bool deliver;
	unsigned long flags;

	local_irq_save(flags);
	arch_spin_lock(&ics->lock);

	state->server = server;
	state->priority = priority;
	state->saved_priority = saved_priority;
	deliver = false;
	if ((state->masked_pending || state->resend) && priority != MASKED) {
		state->masked_pending = 0;
		state->resend = 0;
		deliver = true;
	}

	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);

	return deliver;
}