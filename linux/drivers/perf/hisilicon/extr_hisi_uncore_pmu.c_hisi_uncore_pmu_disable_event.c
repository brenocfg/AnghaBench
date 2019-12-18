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
struct hw_perf_event {int dummy; } ;
struct perf_event {struct hw_perf_event hw; int /*<<< orphan*/  pmu; } ;
struct hisi_pmu {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_counter_int ) (struct hisi_pmu*,struct hw_perf_event*) ;int /*<<< orphan*/  (* disable_counter ) (struct hisi_pmu*,struct hw_perf_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct hisi_pmu*,struct hw_perf_event*) ; 
 int /*<<< orphan*/  stub2 (struct hisi_pmu*,struct hw_perf_event*) ; 
 struct hisi_pmu* to_hisi_pmu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_uncore_pmu_disable_event(struct perf_event *event)
{
	struct hisi_pmu *hisi_pmu = to_hisi_pmu(event->pmu);
	struct hw_perf_event *hwc = &event->hw;

	hisi_pmu->ops->disable_counter(hisi_pmu, hwc);
	hisi_pmu->ops->disable_counter_int(hisi_pmu, hwc);
}