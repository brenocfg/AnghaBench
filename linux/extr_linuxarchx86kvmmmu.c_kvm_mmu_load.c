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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tlb_flush ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_load_cr3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_sync_roots (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int mmu_alloc_roots (struct kvm_vcpu*) ; 
 int mmu_topup_memory_caches (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 

int kvm_mmu_load(struct kvm_vcpu *vcpu)
{
	int r;

	r = mmu_topup_memory_caches(vcpu);
	if (r)
		goto out;
	r = mmu_alloc_roots(vcpu);
	kvm_mmu_sync_roots(vcpu);
	if (r)
		goto out;
	kvm_mmu_load_cr3(vcpu);
	kvm_x86_ops->tlb_flush(vcpu, true);
out:
	return r;
}