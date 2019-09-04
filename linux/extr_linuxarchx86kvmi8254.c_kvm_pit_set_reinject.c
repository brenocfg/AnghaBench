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
struct kvm_kpit_state {int /*<<< orphan*/  reinject; int /*<<< orphan*/  irq_ack_notifier; } ;
struct kvm_pit {int /*<<< orphan*/  mask_notifier; struct kvm* kvm; struct kvm_kpit_state pit_state; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kvm_pit_reset_reinject (struct kvm_pit*) ; 
 int /*<<< orphan*/  kvm_register_irq_ack_notifier (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_register_irq_mask_notifier (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_unregister_irq_ack_notifier (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_unregister_irq_mask_notifier (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void kvm_pit_set_reinject(struct kvm_pit *pit, bool reinject)
{
	struct kvm_kpit_state *ps = &pit->pit_state;
	struct kvm *kvm = pit->kvm;

	if (atomic_read(&ps->reinject) == reinject)
		return;

	if (reinject) {
		/* The initial state is preserved while ps->reinject == 0. */
		kvm_pit_reset_reinject(pit);
		kvm_register_irq_ack_notifier(kvm, &ps->irq_ack_notifier);
		kvm_register_irq_mask_notifier(kvm, 0, &pit->mask_notifier);
	} else {
		kvm_unregister_irq_ack_notifier(kvm, &ps->irq_ack_notifier);
		kvm_unregister_irq_mask_notifier(kvm, 0, &pit->mask_notifier);
	}

	atomic_set(&ps->reinject, reinject);
}