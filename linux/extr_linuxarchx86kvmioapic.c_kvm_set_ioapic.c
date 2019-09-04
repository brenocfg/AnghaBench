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
struct kvm_ioapic_state {int /*<<< orphan*/  irr; } ;
struct kvm_ioapic {int /*<<< orphan*/  lock; scalar_t__ irr_delivered; scalar_t__ irr; } ;
struct TYPE_2__ {struct kvm_ioapic* vioapic; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_ioapic_inject_all (struct kvm_ioapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_scan_ioapic_request (struct kvm*) ; 
 int /*<<< orphan*/  memcpy (struct kvm_ioapic*,struct kvm_ioapic_state*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvm_set_ioapic(struct kvm *kvm, struct kvm_ioapic_state *state)
{
	struct kvm_ioapic *ioapic = kvm->arch.vioapic;

	spin_lock(&ioapic->lock);
	memcpy(ioapic, state, sizeof(struct kvm_ioapic_state));
	ioapic->irr = 0;
	ioapic->irr_delivered = 0;
	kvm_make_scan_ioapic_request(kvm);
	kvm_ioapic_inject_all(ioapic, state->irr);
	spin_unlock(&ioapic->lock);
}