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
typedef  int u64 ;
struct perf_event_attr {int dummy; } ;
struct TYPE_2__ {int sample_period; } ;
struct perf_event {TYPE_1__ hw; struct perf_event_attr attr; } ;

/* Variables and functions */
 int ATTR_CFG_GET_FLD (struct perf_event_attr*,int /*<<< orphan*/ ) ; 
 int SYS_PMSIRR_EL1_RND_SHIFT ; 
 int /*<<< orphan*/  arm_spe_event_sanitise_period (struct perf_event*) ; 
 int /*<<< orphan*/  jitter ; 

__attribute__((used)) static u64 arm_spe_event_to_pmsirr(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	u64 reg = 0;

	arm_spe_event_sanitise_period(event);

	reg |= ATTR_CFG_GET_FLD(attr, jitter) << SYS_PMSIRR_EL1_RND_SHIFT;
	reg |= event->hw.sample_period;

	return reg;
}