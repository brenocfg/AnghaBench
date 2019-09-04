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
struct TYPE_3__ {int config; scalar_t__ precise_ip; int sample_period; } ;
struct TYPE_4__ {int config; } ;
struct perf_event {TYPE_1__ attr; TYPE_2__ hw; } ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ANY ; 
 int EOPNOTSUPP ; 
 int HSW_IN_TX ; 
 int HSW_IN_TX_CHECKPOINTED ; 
 int /*<<< orphan*/  X86_FEATURE_HLE ; 
 int /*<<< orphan*/  X86_FEATURE_RTM ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ event_is_checkpointed (struct perf_event*) ; 
 int intel_pmu_hw_config (struct perf_event*) ; 

__attribute__((used)) static int hsw_hw_config(struct perf_event *event)
{
	int ret = intel_pmu_hw_config(event);

	if (ret)
		return ret;
	if (!boot_cpu_has(X86_FEATURE_RTM) && !boot_cpu_has(X86_FEATURE_HLE))
		return 0;
	event->hw.config |= event->attr.config & (HSW_IN_TX|HSW_IN_TX_CHECKPOINTED);

	/*
	 * IN_TX/IN_TX-CP filters are not supported by the Haswell PMU with
	 * PEBS or in ANY thread mode. Since the results are non-sensical forbid
	 * this combination.
	 */
	if ((event->hw.config & (HSW_IN_TX|HSW_IN_TX_CHECKPOINTED)) &&
	     ((event->hw.config & ARCH_PERFMON_EVENTSEL_ANY) ||
	      event->attr.precise_ip > 0))
		return -EOPNOTSUPP;

	if (event_is_checkpointed(event)) {
		/*
		 * Sampling of checkpointed events can cause situations where
		 * the CPU constantly aborts because of a overflow, which is
		 * then checkpointed back and ignored. Forbid checkpointing
		 * for sampling.
		 *
		 * But still allow a long sampling period, so that perf stat
		 * from KVM works.
		 */
		if (event->attr.sample_period > 0 &&
		    event->attr.sample_period < 0x7fffffff)
			return -EOPNOTSUPP;
	}
	return 0;
}