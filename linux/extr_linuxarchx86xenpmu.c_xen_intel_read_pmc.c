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
typedef  int uint8_t ;
typedef  unsigned long long uint64_t ;
typedef  scalar_t__ uint32_t ;
struct xen_pmu_intel_ctxt {int dummy; } ;
struct TYPE_3__ {struct xen_pmu_intel_ctxt intel; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
struct xen_pmu_data {TYPE_2__ pmu; } ;
struct xen_pmu_cntr_pair {unsigned long long counter; } ;

/* Variables and functions */
 int INTEL_PMC_TYPE_SHIFT ; 
 scalar_t__ MSR_CORE_PERF_FIXED_CTR0 ; 
 scalar_t__ MSR_IA32_PERFCTR0 ; 
 int XENPMU_IRQ_PROCESSING ; 
 unsigned long long* arch_counters ; 
 void* field_offset (struct xen_pmu_intel_ctxt*,unsigned long long*) ; 
 struct xen_pmu_data* get_xenpmu_data () ; 
 int get_xenpmu_flags () ; 
 unsigned long long native_read_msr_safe (scalar_t__,int*) ; 

__attribute__((used)) static unsigned long long xen_intel_read_pmc(int counter)
{
	struct xen_pmu_intel_ctxt *ctxt;
	uint64_t *fixed_counters;
	struct xen_pmu_cntr_pair *arch_cntr_pair;
	struct xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uint8_t xenpmu_flags = get_xenpmu_flags();

	if (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING)) {
		uint32_t msr;
		int err;

		if (counter & (1 << INTEL_PMC_TYPE_SHIFT))
			msr = MSR_CORE_PERF_FIXED_CTR0 + (counter & 0xffff);
		else
			msr = MSR_IA32_PERFCTR0 + counter;

		return native_read_msr_safe(msr, &err);
	}

	ctxt = &xenpmu_data->pmu.c.intel;
	if (counter & (1 << INTEL_PMC_TYPE_SHIFT)) {
		fixed_counters = field_offset(ctxt, fixed_counters);
		return fixed_counters[counter & 0xffff];
	}

	arch_cntr_pair = field_offset(ctxt, arch_counters);
	return arch_cntr_pair[counter].counter;
}