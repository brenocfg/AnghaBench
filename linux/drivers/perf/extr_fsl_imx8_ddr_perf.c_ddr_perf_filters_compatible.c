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
struct perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ ddr_perf_filter_val (struct perf_event*) ; 
 int /*<<< orphan*/  ddr_perf_is_filtered (struct perf_event*) ; 

__attribute__((used)) static bool ddr_perf_filters_compatible(struct perf_event *a,
					struct perf_event *b)
{
	if (!ddr_perf_is_filtered(a))
		return true;
	if (!ddr_perf_is_filtered(b))
		return true;
	return ddr_perf_filter_val(a) == ddr_perf_filter_val(b);
}