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
struct kvmppc_xive_irq_state {int /*<<< orphan*/  saved_priority; } ;
struct kvmppc_xive {int dummy; } ;
struct TYPE_2__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 struct kvmppc_xive_src_block* kvmppc_xive_find_source (struct kvmppc_xive*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_lock_and_mask (struct kvmppc_xive*,struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*) ; 

int kvmppc_xive_int_off(struct kvm *kvm, u32 irq)
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

	pr_devel("int_off(irq=0x%x)\n", irq);

	/*
	 * Lock and mask
	 */
	state->saved_priority = xive_lock_and_mask(xive, sb, state);
	arch_spin_unlock(&sb->lock);

	return 0;
}