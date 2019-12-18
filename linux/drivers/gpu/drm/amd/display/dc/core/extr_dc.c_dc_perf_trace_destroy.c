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
struct dc_perf_trace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct dc_perf_trace*) ; 

__attribute__((used)) static void dc_perf_trace_destroy(struct dc_perf_trace **perf_trace)
{
	kfree(*perf_trace);
	*perf_trace = NULL;
}