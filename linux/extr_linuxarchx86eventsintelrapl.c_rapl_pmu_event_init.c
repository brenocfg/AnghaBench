#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct rapl_pmu {int /*<<< orphan*/  cpu; } ;
struct TYPE_7__ {int event_base; int config; int idx; } ;
struct TYPE_6__ {int config; scalar_t__ type; scalar_t__ sample_period; scalar_t__ exclude_guest; scalar_t__ exclude_host; scalar_t__ exclude_idle; scalar_t__ exclude_hv; scalar_t__ exclude_kernel; scalar_t__ exclude_user; } ;
struct perf_event {TYPE_3__ hw; struct rapl_pmu* pmu_private; int /*<<< orphan*/  cpu; TYPE_2__ attr; int /*<<< orphan*/  event_caps; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_8__ {TYPE_1__ pmu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  INTEL_RAPL_PKG 132 
#define  INTEL_RAPL_PP0 131 
#define  INTEL_RAPL_PP1 130 
#define  INTEL_RAPL_PSYS 129 
#define  INTEL_RAPL_RAM 128 
 int MSR_DRAM_ENERGY_STATUS ; 
 int MSR_PKG_ENERGY_STATUS ; 
 int MSR_PLATFORM_ENERGY_STATUS ; 
 int MSR_PP0_ENERGY_STATUS ; 
 int MSR_PP1_ENERGY_STATUS ; 
 int /*<<< orphan*/  PERF_EV_CAP_READ_ACTIVE_PKG ; 
 int RAPL_EVENT_MASK ; 
 int RAPL_IDX_PKG_NRG_STAT ; 
 int RAPL_IDX_PP0_NRG_STAT ; 
 int RAPL_IDX_PP1_NRG_STAT ; 
 int RAPL_IDX_PSYS_NRG_STAT ; 
 int RAPL_IDX_RAM_NRG_STAT ; 
 struct rapl_pmu* cpu_to_rapl_pmu (int /*<<< orphan*/ ) ; 
 int rapl_cntr_mask ; 
 TYPE_4__* rapl_pmus ; 

__attribute__((used)) static int rapl_pmu_event_init(struct perf_event *event)
{
	u64 cfg = event->attr.config & RAPL_EVENT_MASK;
	int bit, msr, ret = 0;
	struct rapl_pmu *pmu;

	/* only look at RAPL events */
	if (event->attr.type != rapl_pmus->pmu.type)
		return -ENOENT;

	/* check only supported bits are set */
	if (event->attr.config & ~RAPL_EVENT_MASK)
		return -EINVAL;

	if (event->cpu < 0)
		return -EINVAL;

	event->event_caps |= PERF_EV_CAP_READ_ACTIVE_PKG;

	/*
	 * check event is known (determines counter)
	 */
	switch (cfg) {
	case INTEL_RAPL_PP0:
		bit = RAPL_IDX_PP0_NRG_STAT;
		msr = MSR_PP0_ENERGY_STATUS;
		break;
	case INTEL_RAPL_PKG:
		bit = RAPL_IDX_PKG_NRG_STAT;
		msr = MSR_PKG_ENERGY_STATUS;
		break;
	case INTEL_RAPL_RAM:
		bit = RAPL_IDX_RAM_NRG_STAT;
		msr = MSR_DRAM_ENERGY_STATUS;
		break;
	case INTEL_RAPL_PP1:
		bit = RAPL_IDX_PP1_NRG_STAT;
		msr = MSR_PP1_ENERGY_STATUS;
		break;
	case INTEL_RAPL_PSYS:
		bit = RAPL_IDX_PSYS_NRG_STAT;
		msr = MSR_PLATFORM_ENERGY_STATUS;
		break;
	default:
		return -EINVAL;
	}
	/* check event supported */
	if (!(rapl_cntr_mask & (1 << bit)))
		return -EINVAL;

	/* unsupported modes and filters */
	if (event->attr.exclude_user   ||
	    event->attr.exclude_kernel ||
	    event->attr.exclude_hv     ||
	    event->attr.exclude_idle   ||
	    event->attr.exclude_host   ||
	    event->attr.exclude_guest  ||
	    event->attr.sample_period) /* no sampling */
		return -EINVAL;

	/* must be done before validate_group */
	pmu = cpu_to_rapl_pmu(event->cpu);
	if (!pmu)
		return -EINVAL;
	event->cpu = pmu->cpu;
	event->pmu_private = pmu;
	event->hw.event_base = msr;
	event->hw.config = cfg;
	event->hw.idx = bit;

	return ret;
}