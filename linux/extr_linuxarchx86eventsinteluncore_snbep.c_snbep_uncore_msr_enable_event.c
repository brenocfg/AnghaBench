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
struct hw_perf_event_extra {scalar_t__ idx; int /*<<< orphan*/  reg; } ;
struct hw_perf_event {int config; int /*<<< orphan*/  config_base; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {int dummy; } ;

/* Variables and functions */
 scalar_t__ EXTRA_REG_NONE ; 
 int SNBEP_PMON_CTL_EN ; 
 int uncore_shared_reg_config (struct intel_uncore_box*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snbep_uncore_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;

	if (reg1->idx != EXTRA_REG_NONE)
		wrmsrl(reg1->reg, uncore_shared_reg_config(box, 0));

	wrmsrl(hwc->config_base, hwc->config | SNBEP_PMON_CTL_EN);
}