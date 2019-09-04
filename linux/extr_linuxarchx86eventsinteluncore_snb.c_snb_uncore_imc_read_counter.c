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
typedef  int /*<<< orphan*/  u64 ;
struct hw_perf_event {scalar_t__ event_base; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {scalar_t__ io_addr; } ;

/* Variables and functions */

__attribute__((used)) static u64 snb_uncore_imc_read_counter(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;

	return (u64)*(unsigned int *)(box->io_addr + hwc->event_base);
}