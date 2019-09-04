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
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int /*<<< orphan*/ * amd_f17h_perfmon_event_map ; 
 int /*<<< orphan*/ * amd_perfmon_event_map ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static u64 amd_pmu_event_map(int hw_event)
{
	if (boot_cpu_data.x86 >= 0x17)
		return amd_f17h_perfmon_event_map[hw_event];

	return amd_perfmon_event_map[hw_event];
}