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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u64 ;
struct xen_pmu_intel_ctxt {int /*<<< orphan*/  global_status; int /*<<< orphan*/  fixed_ctrl; int /*<<< orphan*/  global_ctrl; int /*<<< orphan*/  global_ovf_ctrl; } ;
struct TYPE_3__ {struct xen_pmu_intel_ctxt intel; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
struct xen_pmu_data {TYPE_2__ pmu; } ;
struct xen_pmu_cntr_pair {int /*<<< orphan*/  control; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
#define  MSR_CORE_PERF_FIXED_CTR_CTRL 134 
#define  MSR_CORE_PERF_GLOBAL_CTRL 133 
#define  MSR_CORE_PERF_GLOBAL_OVF_CTRL 132 
#define  MSR_CORE_PERF_GLOBAL_STATUS 131 
#define  MSR_TYPE_ARCH_COUNTER 130 
#define  MSR_TYPE_ARCH_CTRL 129 
#define  MSR_TYPE_COUNTER 128 
 int XENPMU_IRQ_PROCESSING ; 
 int /*<<< orphan*/  arch_counters ; 
 void* field_offset (struct xen_pmu_intel_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixed_counters ; 
 struct xen_pmu_data* get_xenpmu_data () ; 
 int get_xenpmu_flags () ; 

__attribute__((used)) static bool xen_intel_pmu_emulate(unsigned int msr, u64 *val, int type,
				  int index, bool is_read)
{
	uint64_t *reg = NULL;
	struct xen_pmu_intel_ctxt *ctxt;
	uint64_t *fix_counters;
	struct xen_pmu_cntr_pair *arch_cntr_pair;
	struct xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uint8_t xenpmu_flags = get_xenpmu_flags();


	if (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING))
		return false;

	ctxt = &xenpmu_data->pmu.c.intel;

	switch (msr) {
	case MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		reg = &ctxt->global_ovf_ctrl;
		break;
	case MSR_CORE_PERF_GLOBAL_STATUS:
		reg = &ctxt->global_status;
		break;
	case MSR_CORE_PERF_GLOBAL_CTRL:
		reg = &ctxt->global_ctrl;
		break;
	case MSR_CORE_PERF_FIXED_CTR_CTRL:
		reg = &ctxt->fixed_ctrl;
		break;
	default:
		switch (type) {
		case MSR_TYPE_COUNTER:
			fix_counters = field_offset(ctxt, fixed_counters);
			reg = &fix_counters[index];
			break;
		case MSR_TYPE_ARCH_COUNTER:
			arch_cntr_pair = field_offset(ctxt, arch_counters);
			reg = &arch_cntr_pair[index].counter;
			break;
		case MSR_TYPE_ARCH_CTRL:
			arch_cntr_pair = field_offset(ctxt, arch_counters);
			reg = &arch_cntr_pair[index].control;
			break;
		default:
			return false;
		}
	}

	if (reg) {
		if (is_read)
			*val = *reg;
		else {
			*reg = *val;

			if (msr == MSR_CORE_PERF_GLOBAL_OVF_CTRL)
				ctxt->global_status &= (~(*val));
		}
		return true;
	}

	return false;
}