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
struct perf_event {int /*<<< orphan*/  cpu; } ;
struct amd_uncore {int dummy; } ;

/* Variables and functions */
 scalar_t__ amd_uncore_llc ; 
 scalar_t__ amd_uncore_nb ; 
 scalar_t__ is_llc_event (struct perf_event*) ; 
 scalar_t__ is_nb_event (struct perf_event*) ; 
 struct amd_uncore** per_cpu_ptr (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct amd_uncore *event_to_amd_uncore(struct perf_event *event)
{
	if (is_nb_event(event) && amd_uncore_nb)
		return *per_cpu_ptr(amd_uncore_nb, event->cpu);
	else if (is_llc_event(event) && amd_uncore_llc)
		return *per_cpu_ptr(amd_uncore_llc, event->cpu);

	return NULL;
}