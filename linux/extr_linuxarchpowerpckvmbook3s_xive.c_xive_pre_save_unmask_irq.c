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
typedef  size_t u32 ;
struct kvmppc_xive_src_block {int /*<<< orphan*/  lock; struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {scalar_t__ saved_scan_prio; int /*<<< orphan*/  valid; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_finish_unmask (struct kvmppc_xive*,struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*,scalar_t__) ; 
 int /*<<< orphan*/  xive_lock_for_unmask (struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*) ; 

__attribute__((used)) static void xive_pre_save_unmask_irq(struct kvmppc_xive *xive,
				     struct kvmppc_xive_src_block *sb,
				     u32 irq)
{
	struct kvmppc_xive_irq_state *state = &sb->irq_state[irq];

	if (!state->valid)
		return;

	/*
	 * Lock / exclude EOI (not technically necessary if the
	 * guest isn't running concurrently. If this becomes a
	 * performance issue we can probably remove the lock.
	 */
	xive_lock_for_unmask(sb, state);

	/* Restore mask/prio if it wasn't masked */
	if (state->saved_scan_prio != MASKED)
		xive_finish_unmask(xive, sb, state, state->saved_scan_prio);

	/* Unlock */
	arch_spin_unlock(&sb->lock);
}