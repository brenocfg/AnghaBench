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
typedef  int u8 ;
struct kvm_pmc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pmu_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* find_fixed_event ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_HARDWARE ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  pmc_is_enabled (struct kvm_pmc*) ; 
 int /*<<< orphan*/  pmc_reprogram_counter (struct kvm_pmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  pmc_stop_counter (struct kvm_pmc*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

void reprogram_fixed_counter(struct kvm_pmc *pmc, u8 ctrl, int idx)
{
	unsigned en_field = ctrl & 0x3;
	bool pmi = ctrl & 0x8;

	pmc_stop_counter(pmc);

	if (!en_field || !pmc_is_enabled(pmc))
		return;

	pmc_reprogram_counter(pmc, PERF_TYPE_HARDWARE,
			      kvm_x86_ops->pmu_ops->find_fixed_event(idx),
			      !(en_field & 0x2), /* exclude user */
			      !(en_field & 0x1), /* exclude kernel */
			      pmi, false, false);
}