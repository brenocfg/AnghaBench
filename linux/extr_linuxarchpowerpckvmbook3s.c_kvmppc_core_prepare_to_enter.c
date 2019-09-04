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
struct TYPE_2__ {unsigned long pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 unsigned int BOOK3S_IRQPRIO_MAX ; 
 unsigned int __ffs (unsigned long) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,unsigned long*) ; 
 scalar_t__ clear_irqprio (struct kvm_vcpu*,unsigned int) ; 
 unsigned int find_next_bit (unsigned long*,int,unsigned int) ; 
 scalar_t__ kvmppc_book3s_irqprio_deliver (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_update_int_pending (struct kvm_vcpu*,unsigned long,unsigned long) ; 

int kvmppc_core_prepare_to_enter(struct kvm_vcpu *vcpu)
{
	unsigned long *pending = &vcpu->arch.pending_exceptions;
	unsigned long old_pending = vcpu->arch.pending_exceptions;
	unsigned int priority;

#ifdef EXIT_DEBUG
	if (vcpu->arch.pending_exceptions)
		printk(KERN_EMERG "KVM: Check pending: %lx\n", vcpu->arch.pending_exceptions);
#endif
	priority = __ffs(*pending);
	while (priority < BOOK3S_IRQPRIO_MAX) {
		if (kvmppc_book3s_irqprio_deliver(vcpu, priority) &&
		    clear_irqprio(vcpu, priority)) {
			clear_bit(priority, &vcpu->arch.pending_exceptions);
			break;
		}

		priority = find_next_bit(pending,
					 BITS_PER_BYTE * sizeof(*pending),
					 priority + 1);
	}

	/* Tell the guest about our interrupt status */
	kvmppc_update_int_pending(vcpu, *pending, old_pending);

	return 0;
}