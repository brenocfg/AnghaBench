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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_pmu {int /*<<< orphan*/  fixed_ctr_ctrl; } ;
struct kvm_pmc {int /*<<< orphan*/  eventsel; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {struct kvm_pmc* (* pmc_idx_to_pmc ) (struct kvm_pmu*,int) ;} ;

/* Variables and functions */
 int INTEL_PMC_IDX_FIXED ; 
 int /*<<< orphan*/  fixed_ctrl_field (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ pmc_is_gp (struct kvm_pmc*) ; 
 int /*<<< orphan*/  reprogram_fixed_counter (struct kvm_pmc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reprogram_gp_counter (struct kvm_pmc*,int /*<<< orphan*/ ) ; 
 struct kvm_pmc* stub1 (struct kvm_pmu*,int) ; 

void reprogram_counter(struct kvm_pmu *pmu, int pmc_idx)
{
	struct kvm_pmc *pmc = kvm_x86_ops->pmu_ops->pmc_idx_to_pmc(pmu, pmc_idx);

	if (!pmc)
		return;

	if (pmc_is_gp(pmc))
		reprogram_gp_counter(pmc, pmc->eventsel);
	else {
		int idx = pmc_idx - INTEL_PMC_IDX_FIXED;
		u8 ctrl = fixed_ctrl_field(pmu->fixed_ctr_ctrl, idx);

		reprogram_fixed_counter(pmc, ctrl, idx);
	}
}