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
struct perf_event {int /*<<< orphan*/ * pmu; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmu; } ;

/* Variables and functions */

__attribute__((used)) static bool is_box_event(struct intel_uncore_box *box, struct perf_event *event)
{
	return &box->pmu->pmu == event->pmu;
}