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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct hw_perf_event {int idx; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct TYPE_4__ {int /*<<< orphan*/  config_lock; scalar_t__ base; } ;
struct arm_ccn {TYPE_2__ dt; } ;

/* Variables and functions */
 scalar_t__ CCN_CONFIG_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCN_CONFIG_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ CCN_CONFIG_TYPE (int /*<<< orphan*/ ) ; 
 int CCN_CONFIG_XP (int /*<<< orphan*/ ) ; 
 scalar_t__ CCN_DT_ACTIVE_DSM ; 
 int CCN_DT_ACTIVE_DSM__DSM_ID__MASK ; 
 int CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT (int) ; 
 scalar_t__ CCN_EVENT_WATCHPOINT ; 
 int CCN_IDX_PMU_CYCLE_COUNTER ; 
 scalar_t__ CCN_TYPE_XP ; 
 int arm_ccn_node_to_xp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ccn_pmu_node_event_config (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_xp_event_config (struct perf_event*) ; 
 int /*<<< orphan*/  arm_ccn_pmu_xp_watchpoint_config (struct perf_event*) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void arm_ccn_pmu_event_config(struct perf_event *event)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	struct hw_perf_event *hw = &event->hw;
	u32 xp, offset, val;

	/* Cycle counter requires no setup */
	if (hw->idx == CCN_IDX_PMU_CYCLE_COUNTER)
		return;

	if (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP)
		xp = CCN_CONFIG_XP(event->attr.config);
	else
		xp = arm_ccn_node_to_xp(CCN_CONFIG_NODE(event->attr.config));

	spin_lock(&ccn->dt.config_lock);

	/* Set the DT bus "distance" register */
	offset = (hw->idx / 4) * 4;
	val = readl(ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);
	val &= ~(CCN_DT_ACTIVE_DSM__DSM_ID__MASK <<
			CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4));
	val |= xp << CCN_DT_ACTIVE_DSM__DSM_ID__SHIFT(hw->idx % 4);
	writel(val, ccn->dt.base + CCN_DT_ACTIVE_DSM + offset);

	if (CCN_CONFIG_TYPE(event->attr.config) == CCN_TYPE_XP) {
		if (CCN_CONFIG_EVENT(event->attr.config) ==
				CCN_EVENT_WATCHPOINT)
			arm_ccn_pmu_xp_watchpoint_config(event);
		else
			arm_ccn_pmu_xp_event_config(event);
	} else {
		arm_ccn_pmu_node_event_config(event);
	}

	spin_unlock(&ccn->dt.config_lock);
}