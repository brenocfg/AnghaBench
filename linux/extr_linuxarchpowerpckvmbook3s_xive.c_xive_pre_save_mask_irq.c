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
struct kvmppc_xive_irq_state {int /*<<< orphan*/  old_q; int /*<<< orphan*/  saved_q; int /*<<< orphan*/  old_p; int /*<<< orphan*/  saved_p; int /*<<< orphan*/  saved_scan_prio; int /*<<< orphan*/  valid; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_lock_and_mask (struct kvmppc_xive*,struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*) ; 

__attribute__((used)) static void xive_pre_save_mask_irq(struct kvmppc_xive *xive,
				   struct kvmppc_xive_src_block *sb,
				   u32 irq)
{
	struct kvmppc_xive_irq_state *state = &sb->irq_state[irq];

	if (!state->valid)
		return;

	/* Mask and save state, this will also sync HW queues */
	state->saved_scan_prio = xive_lock_and_mask(xive, sb, state);

	/* Transfer P and Q */
	state->saved_p = state->old_p;
	state->saved_q = state->old_q;

	/* Unlock */
	arch_spin_unlock(&sb->lock);
}