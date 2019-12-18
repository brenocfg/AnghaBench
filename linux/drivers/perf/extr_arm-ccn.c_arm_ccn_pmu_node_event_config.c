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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  config; } ;
struct hw_perf_event {size_t idx; int config_base; int /*<<< orphan*/  event_base; } ;
struct perf_event {TYPE_3__ attr; struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct arm_ccn_component {scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__* pmu_counters; } ;
struct arm_ccn {TYPE_2__ dt; } ;
struct TYPE_4__ {struct arm_ccn_component* source; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ CCN_CONFIG_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCN_CONFIG_NODE (int /*<<< orphan*/ ) ; 
 scalar_t__ CCN_CONFIG_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ CCN_HNF_PMU_EVENT_SEL ; 
 scalar_t__ CCN_HNF_PMU_EVENT_SEL__ID__MASK ; 
 scalar_t__ CCN_HNF_PMU_EVENT_SEL__ID__SHIFT (int) ; 
 scalar_t__ CCN_RNI_PMU_EVENT_SEL ; 
 scalar_t__ CCN_RNI_PMU_EVENT_SEL__ID__MASK ; 
 scalar_t__ CCN_RNI_PMU_EVENT_SEL__ID__SHIFT (int) ; 
 scalar_t__ CCN_SBAS_PMU_EVENT_SEL ; 
 scalar_t__ CCN_SBAS_PMU_EVENT_SEL__ID__MASK ; 
 scalar_t__ CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT (int) ; 
 scalar_t__ CCN_TYPE_HNF ; 
 int /*<<< orphan*/  CCN_TYPE_RNI_3P ; 
 scalar_t__ CCN_TYPE_SBAS ; 
 int /*<<< orphan*/  CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT (scalar_t__,int) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ arm_ccn_node_to_xp_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ccn_pmu_type_eq (scalar_t__,int /*<<< orphan*/ ) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void arm_ccn_pmu_node_event_config(struct perf_event *event)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(event->pmu);
	struct hw_perf_event *hw = &event->hw;
	struct arm_ccn_component *source =
			ccn->dt.pmu_counters[hw->idx].source;
	u32 type = CCN_CONFIG_TYPE(event->attr.config);
	u32 val, port;

	port = arm_ccn_node_to_xp_port(CCN_CONFIG_NODE(event->attr.config));
	hw->event_base = CCN_XP_DT_CONFIG__DT_CFG__DEVICE_PMU_EVENT(port,
			hw->config_base);

	/* These *_event_sel regs should be identical, but let's make sure... */
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL != CCN_SBAS_PMU_EVENT_SEL);
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL != CCN_RNI_PMU_EVENT_SEL);
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(1) !=
			CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT(1));
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL__ID__SHIFT(1) !=
			CCN_RNI_PMU_EVENT_SEL__ID__SHIFT(1));
	BUILD_BUG_ON(CCN_HNF_PMU_EVENT_SEL__ID__MASK !=
			CCN_SBAS_PMU_EVENT_SEL__ID__MASK);
	BUILD_BUG_ON(CCN_SBAS_PMU_EVENT_SEL__ID__MASK !=
			CCN_RNI_PMU_EVENT_SEL__ID__MASK);
	if (WARN_ON(type != CCN_TYPE_HNF && type != CCN_TYPE_SBAS &&
			!arm_ccn_pmu_type_eq(type, CCN_TYPE_RNI_3P)))
		return;

	/* Set the event id for the pre-allocated counter */
	val = readl(source->base + CCN_HNF_PMU_EVENT_SEL);
	val &= ~(CCN_HNF_PMU_EVENT_SEL__ID__MASK <<
		CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(hw->config_base));
	val |= CCN_CONFIG_EVENT(event->attr.config) <<
		CCN_HNF_PMU_EVENT_SEL__ID__SHIFT(hw->config_base);
	writel(val, source->base + CCN_HNF_PMU_EVENT_SEL);
}