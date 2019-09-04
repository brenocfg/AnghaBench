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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool kvm_vcpu_trigger_posted_interrupt(struct kvm_vcpu *vcpu,
						     bool nested)
{
#ifdef CONFIG_SMP
	int pi_vec = nested ? POSTED_INTR_NESTED_VECTOR : POSTED_INTR_VECTOR;

	if (vcpu->mode == IN_GUEST_MODE) {
		/*
		 * The vector of interrupt to be delivered to vcpu had
		 * been set in PIR before this function.
		 *
		 * Following cases will be reached in this block, and
		 * we always send a notification event in all cases as
		 * explained below.
		 *
		 * Case 1: vcpu keeps in non-root mode. Sending a
		 * notification event posts the interrupt to vcpu.
		 *
		 * Case 2: vcpu exits to root mode and is still
		 * runnable. PIR will be synced to vIRR before the
		 * next vcpu entry. Sending a notification event in
		 * this case has no effect, as vcpu is not in root
		 * mode.
		 *
		 * Case 3: vcpu exits to root mode and is blocked.
		 * vcpu_block() has already synced PIR to vIRR and
		 * never blocks vcpu if vIRR is not cleared. Therefore,
		 * a blocked vcpu here does not wait for any requested
		 * interrupts in PIR, and sending a notification event
		 * which has no effect is safe here.
		 */

		apic->send_IPI_mask(get_cpu_mask(vcpu->cpu), pi_vec);
		return true;
	}
#endif
	return false;
}