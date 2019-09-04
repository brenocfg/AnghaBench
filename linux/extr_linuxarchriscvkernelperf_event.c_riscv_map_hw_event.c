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
typedef  size_t u64 ;
struct TYPE_2__ {size_t max_events; int* hw_events; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* riscv_pmu ; 

__attribute__((used)) static int riscv_map_hw_event(u64 config)
{
	if (config >= riscv_pmu->max_events)
		return -EINVAL;

	return riscv_pmu->hw_events[config];
}