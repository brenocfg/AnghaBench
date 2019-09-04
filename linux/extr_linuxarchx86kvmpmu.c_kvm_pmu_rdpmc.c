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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_pmc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {struct kvm_pmc* (* msr_idx_to_pmc ) (struct kvm_vcpu*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ is_vmware_backdoor_pmc (unsigned int) ; 
 int kvm_pmu_rdpmc_vmware (struct kvm_vcpu*,unsigned int,scalar_t__*) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ pmc_read_counter (struct kvm_pmc*) ; 
 struct kvm_pmc* stub1 (struct kvm_vcpu*,unsigned int) ; 

int kvm_pmu_rdpmc(struct kvm_vcpu *vcpu, unsigned idx, u64 *data)
{
	bool fast_mode = idx & (1u << 31);
	struct kvm_pmc *pmc;
	u64 ctr_val;

	if (is_vmware_backdoor_pmc(idx))
		return kvm_pmu_rdpmc_vmware(vcpu, idx, data);

	pmc = kvm_x86_ops->pmu_ops->msr_idx_to_pmc(vcpu, idx);
	if (!pmc)
		return 1;

	ctr_val = pmc_read_counter(pmc);
	if (fast_mode)
		ctr_val = (u32)ctr_val;

	*data = ctr_val;
	return 0;
}