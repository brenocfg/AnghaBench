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
struct amd_uncore {unsigned int cpu; int id; int /*<<< orphan*/ * pmu; int /*<<< orphan*/ * active_mask; int /*<<< orphan*/  msr_base; int /*<<< orphan*/  rdpmc_base; int /*<<< orphan*/  num_counters; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MSR_F15H_NB_PERF_CTL ; 
 int /*<<< orphan*/  MSR_F16H_L2I_PERF_CTL ; 
 int /*<<< orphan*/  RDPMC_BASE_LLC ; 
 int /*<<< orphan*/  RDPMC_BASE_NB ; 
 int /*<<< orphan*/  amd_llc_active_mask ; 
 int /*<<< orphan*/  amd_llc_pmu ; 
 int /*<<< orphan*/  amd_nb_active_mask ; 
 int /*<<< orphan*/  amd_nb_pmu ; 
 struct amd_uncore* amd_uncore_alloc (unsigned int) ; 
 scalar_t__ amd_uncore_llc ; 
 scalar_t__ amd_uncore_nb ; 
 int /*<<< orphan*/  kfree (struct amd_uncore*) ; 
 int /*<<< orphan*/  num_counters_llc ; 
 int /*<<< orphan*/  num_counters_nb ; 
 struct amd_uncore** per_cpu_ptr (scalar_t__,unsigned int) ; 

__attribute__((used)) static int amd_uncore_cpu_up_prepare(unsigned int cpu)
{
	struct amd_uncore *uncore_nb = NULL, *uncore_llc;

	if (amd_uncore_nb) {
		uncore_nb = amd_uncore_alloc(cpu);
		if (!uncore_nb)
			goto fail;
		uncore_nb->cpu = cpu;
		uncore_nb->num_counters = num_counters_nb;
		uncore_nb->rdpmc_base = RDPMC_BASE_NB;
		uncore_nb->msr_base = MSR_F15H_NB_PERF_CTL;
		uncore_nb->active_mask = &amd_nb_active_mask;
		uncore_nb->pmu = &amd_nb_pmu;
		uncore_nb->id = -1;
		*per_cpu_ptr(amd_uncore_nb, cpu) = uncore_nb;
	}

	if (amd_uncore_llc) {
		uncore_llc = amd_uncore_alloc(cpu);
		if (!uncore_llc)
			goto fail;
		uncore_llc->cpu = cpu;
		uncore_llc->num_counters = num_counters_llc;
		uncore_llc->rdpmc_base = RDPMC_BASE_LLC;
		uncore_llc->msr_base = MSR_F16H_L2I_PERF_CTL;
		uncore_llc->active_mask = &amd_llc_active_mask;
		uncore_llc->pmu = &amd_llc_pmu;
		uncore_llc->id = -1;
		*per_cpu_ptr(amd_uncore_llc, cpu) = uncore_llc;
	}

	return 0;

fail:
	if (amd_uncore_nb)
		*per_cpu_ptr(amd_uncore_nb, cpu) = NULL;
	kfree(uncore_nb);
	return -ENOMEM;
}