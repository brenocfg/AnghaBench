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
struct TYPE_4__ {int config1; } ;
struct hw_perf_event_extra {int config; scalar_t__ idx; int /*<<< orphan*/  reg; } ;
struct TYPE_3__ {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; TYPE_1__ hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 int HSWEP_U_MSR_PMON_BOX_FILTER_MASK ; 
 int /*<<< orphan*/  HSWEP_U_MSR_PMON_FILTER ; 

__attribute__((used)) static int hswep_ubox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;
	reg1->reg = HSWEP_U_MSR_PMON_FILTER;
	reg1->config = event->attr.config1 & HSWEP_U_MSR_PMON_BOX_FILTER_MASK;
	reg1->idx = 0;
	return 0;
}