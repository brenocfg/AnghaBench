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
struct TYPE_2__ {int radix; int /*<<< orphan*/  hpt; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int LPCR_GTSE ; 
 int LPCR_HR ; 
 int LPCR_UPRT ; 
 int LPCR_VPM1 ; 
 int /*<<< orphan*/  kvmppc_free_hpt (int /*<<< orphan*/ *) ; 
 int kvmppc_init_vm_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_update_lpcr (struct kvm*,int,int) ; 

int kvmppc_switch_mmu_to_radix(struct kvm *kvm)
{
	int err;

	err = kvmppc_init_vm_radix(kvm);
	if (err)
		return err;

	kvmppc_free_hpt(&kvm->arch.hpt);
	kvmppc_update_lpcr(kvm, LPCR_UPRT | LPCR_GTSE | LPCR_HR,
			   LPCR_VPM1 | LPCR_UPRT | LPCR_GTSE | LPCR_HR);
	kvm->arch.radix = 1;
	return 0;
}