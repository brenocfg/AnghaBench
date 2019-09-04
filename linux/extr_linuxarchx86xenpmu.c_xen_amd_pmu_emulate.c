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
struct xen_pmu_amd_ctxt {int dummy; } ;
struct TYPE_3__ {struct xen_pmu_amd_ctxt amd; } ;
struct TYPE_4__ {TYPE_1__ c; } ;
struct xen_pmu_data {TYPE_2__ pmu; } ;

/* Variables and functions */
 unsigned int MSR_K7_EVNTSEL0 ; 
 unsigned int MSR_K7_PERFCTR3 ; 
 int XENPMU_IRQ_PROCESSING ; 
 int amd_counters_base ; 
 int amd_ctrls_base ; 
 scalar_t__ amd_msr_step ; 
 int amd_num_counters ; 
 int /*<<< orphan*/  counters ; 
 int /*<<< orphan*/  ctrls ; 
 int /*<<< orphan*/ * field_offset (struct xen_pmu_amd_ctxt*,int /*<<< orphan*/ ) ; 
 unsigned int get_fam15h_addr (unsigned int) ; 
 struct xen_pmu_data* get_xenpmu_data () ; 
 int get_xenpmu_flags () ; 
 scalar_t__ k7_counters_mirrored ; 

__attribute__((used)) static bool xen_amd_pmu_emulate(unsigned int msr, u64 *val, bool is_read)
{
	uint64_t *reg = NULL;
	int i, off = 0;
	struct xen_pmu_amd_ctxt *ctxt;
	uint64_t *counter_regs, *ctrl_regs;
	struct xen_pmu_data *xenpmu_data = get_xenpmu_data();
	uint8_t xenpmu_flags = get_xenpmu_flags();

	if (!xenpmu_data || !(xenpmu_flags & XENPMU_IRQ_PROCESSING))
		return false;

	if (k7_counters_mirrored &&
	    ((msr >= MSR_K7_EVNTSEL0) && (msr <= MSR_K7_PERFCTR3)))
		msr = get_fam15h_addr(msr);

	ctxt = &xenpmu_data->pmu.c.amd;
	for (i = 0; i < amd_num_counters; i++) {
		if (msr == amd_ctrls_base + off) {
			ctrl_regs = field_offset(ctxt, ctrls);
			reg = &ctrl_regs[i];
			break;
		} else if (msr == amd_counters_base + off) {
			counter_regs = field_offset(ctxt, counters);
			reg = &counter_regs[i];
			break;
		}
		off += amd_msr_step;
	}

	if (reg) {
		if (is_read)
			*val = *reg;
		else
			*reg = *val;

		return true;
	}
	return false;
}