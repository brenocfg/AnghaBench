#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvmppc_xive_vcpu {scalar_t__ server_num; } ;
struct kvmppc_xive_src_block {int /*<<< orphan*/  lock; struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {scalar_t__ act_priority; scalar_t__ act_server; scalar_t__ pt_number; int /*<<< orphan*/ * pt_data; scalar_t__ ipi_number; int /*<<< orphan*/  ipi_data; int /*<<< orphan*/  valid; } ;
struct kvmppc_xive {int max_sbid; struct kvmppc_xive_src_block** src_blocks; } ;
struct TYPE_3__ {struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {struct kvm* kvm; TYPE_1__ arch; } ;
struct TYPE_4__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_01 ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_native_configure_irq (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_esb_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_xive_disable_vcpu_interrupts(struct kvm_vcpu *vcpu)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	struct kvm *kvm = vcpu->kvm;
	struct kvmppc_xive *xive = kvm->arch.xive;
	int i, j;

	for (i = 0; i <= xive->max_sbid; i++) {
		struct kvmppc_xive_src_block *sb = xive->src_blocks[i];

		if (!sb)
			continue;
		for (j = 0; j < KVMPPC_XICS_IRQ_PER_ICS; j++) {
			struct kvmppc_xive_irq_state *state = &sb->irq_state[j];

			if (!state->valid)
				continue;
			if (state->act_priority == MASKED)
				continue;
			if (state->act_server != xc->server_num)
				continue;

			/* Clean it up */
			arch_spin_lock(&sb->lock);
			state->act_priority = MASKED;
			xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);
			xive_native_configure_irq(state->ipi_number, 0, MASKED, 0);
			if (state->pt_number) {
				xive_vm_esb_load(state->pt_data, XIVE_ESB_SET_PQ_01);
				xive_native_configure_irq(state->pt_number, 0, MASKED, 0);
			}
			arch_spin_unlock(&sb->lock);
		}
	}
}