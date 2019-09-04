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
struct TYPE_2__ {scalar_t__ process_table; scalar_t__ radix; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int LPCR_GTSE ; 
 int LPCR_HR ; 
 int LPCR_UPRT ; 
 int LPCR_VPM1 ; 
 int /*<<< orphan*/  kvmppc_free_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_rmap_reset (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_update_lpcr (struct kvm*,int,int) ; 

int kvmppc_switch_mmu_to_hpt(struct kvm *kvm)
{
	kvmppc_free_radix(kvm);
	kvmppc_update_lpcr(kvm, LPCR_VPM1,
			   LPCR_VPM1 | LPCR_UPRT | LPCR_GTSE | LPCR_HR);
	kvmppc_rmap_reset(kvm);
	kvm->arch.radix = 0;
	kvm->arch.process_table = 0;
	return 0;
}