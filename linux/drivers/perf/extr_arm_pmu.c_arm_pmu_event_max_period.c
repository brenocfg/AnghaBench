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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int flags; } ;
struct perf_event {TYPE_1__ hw; } ;

/* Variables and functions */
 int ARMPMU_EVT_64BIT ; 
 int /*<<< orphan*/  GENMASK_ULL (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 arm_pmu_event_max_period(struct perf_event *event)
{
	if (event->hw.flags & ARMPMU_EVT_64BIT)
		return GENMASK_ULL(63, 0);
	else
		return GENMASK_ULL(31, 0);
}