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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct kvmppc_xive_src_block {int /*<<< orphan*/  lock; struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {scalar_t__ act_priority; scalar_t__ saved_priority; } ;
struct kvmppc_xive {int dummy; } ;
struct TYPE_2__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 struct kvmppc_xive_src_block* kvmppc_xive_find_source (struct kvmppc_xive*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  pr_devel (char*,...) ; 
 int /*<<< orphan*/  xive_finish_unmask (struct kvmppc_xive*,struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*,scalar_t__) ; 
 int /*<<< orphan*/  xive_lock_for_unmask (struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*) ; 

int kvmppc_xive_int_on(struct kvm *kvm, u32 irq)
{
	struct kvmppc_xive *xive = kvm->arch.xive;
	struct kvmppc_xive_src_block *sb;
	struct kvmppc_xive_irq_state *state;
	u16 idx;

	if (!xive)
		return -ENODEV;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	if (!sb)
		return -EINVAL;
	state = &sb->irq_state[idx];

	pr_devel("int_on(irq=0x%x)\n", irq);

	/*
	 * Check if interrupt was not targetted
	 */
	if (state->act_priority == MASKED) {
		pr_devel("int_on on untargetted interrupt\n");
		return -EINVAL;
	}

	/* If saved_priority is 0xff, do nothing */
	if (state->saved_priority == MASKED)
		return 0;

	/*
	 * Lock and unmask it.
	 */
	xive_lock_for_unmask(sb, state);
	xive_finish_unmask(xive, sb, state, state->saved_priority);
	arch_spin_unlock(&sb->lock);

	return 0;
}