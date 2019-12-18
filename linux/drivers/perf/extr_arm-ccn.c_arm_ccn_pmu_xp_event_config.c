#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct hw_perf_event {size_t idx; int /*<<< orphan*/  config_base; int /*<<< orphan*/  event_base; } ;
struct perf_event {TYPE_3__ attr; struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_ccn_component {scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__* pmu_counters; } ;
struct arm_ccn {TYPE_2__ dt; } ;
struct TYPE_4__ {struct arm_ccn_component* source; } ;

/* Variables and functions */
 int CCN_CONFIG_BUS (int /*<<< orphan*/ ) ; 
 int CCN_CONFIG_EVENT (int /*<<< orphan*/ ) ; 
 int CCN_CONFIG_VC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ CCN_XP_PMU_EVENT_SEL ; 
 int CCN_XP_PMU_EVENT_SEL__ID__MASK ; 
 int CCN_XP_PMU_EVENT_SEL__ID__SHIFT (int /*<<< orphan*/ ) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void arm_ccn_pmu_xp_event_config(struct perf_event *event)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	struct hw_perf_event *hw = &event->hw;
	struct arm_ccn_component *source =
			ccn->dt.pmu_counters[hw->idx].source;
	u32 val, id;

	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__XP_PMU_EVENT(hw->config_base);

	id = (CCN_CONFIG_VC(event->attr.config) << 4) |
			(CCN_CONFIG_BUS(event->attr.config) << 3) |
			(CCN_CONFIG_EVENT(event->attr.config) << 0);

	val = readl(source->base + CCN_XP_PMU_EVENT_SEL);
	val &= ~(CCN_XP_PMU_EVENT_SEL__ID__MASK <<
			CCN_XP_PMU_EVENT_SEL__ID__SHIFT(hw->config_base));
	val |= id << CCN_XP_PMU_EVENT_SEL__ID__SHIFT(hw->config_base);
	writel(val, source->base + CCN_XP_PMU_EVENT_SEL);
}