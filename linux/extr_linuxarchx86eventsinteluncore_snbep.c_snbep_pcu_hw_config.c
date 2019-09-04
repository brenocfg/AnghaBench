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
struct TYPE_2__ {int config1; } ;
struct hw_perf_event_extra {int idx; int config; int /*<<< orphan*/  reg; } ;
struct hw_perf_event {int config; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNBEP_PCU_MSR_PMON_BOX_FILTER ; 
 int SNBEP_PMON_CTL_EV_SEL_MASK ; 

__attribute__((used)) static int snbep_pcu_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	int ev_sel = hwc->config & SNBEP_PMON_CTL_EV_SEL_MASK;

	if (ev_sel >= 0xb && ev_sel <= 0xe) {
		reg1->reg = SNBEP_PCU_MSR_PMON_BOX_FILTER;
		reg1->idx = ev_sel - 0xb;
		reg1->config = event->attr.config1 & (0xff << (reg1->idx * 8));
	}
	return 0;
}