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
struct kvm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void kvm_gen_update_masterclock(struct kvm *kvm)
{
#ifdef CONFIG_X86_64
	int i;
	struct kvm_vcpu *vcpu;
	struct kvm_arch *ka = &kvm->arch;

	spin_lock(&ka->pvclock_gtod_sync_lock);
	kvm_make_mclock_inprogress_request(kvm);
	/* no guest entries from this point */
	pvclock_update_vm_gtod_copy(kvm);

	kvm_for_each_vcpu(i, vcpu, kvm)
		kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);

	/* guest entries allowed */
	kvm_for_each_vcpu(i, vcpu, kvm)
		kvm_clear_request(KVM_REQ_MCLOCK_INPROGRESS, vcpu);

	spin_unlock(&ka->pvclock_gtod_sync_lock);
#endif
}