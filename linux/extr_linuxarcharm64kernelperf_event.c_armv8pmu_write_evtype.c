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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARMV8_PMU_EVTYPE_MASK ; 
 int /*<<< orphan*/  armv8pmu_select_counter (int) ; 
 int /*<<< orphan*/  pmxevtyper_el0 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void armv8pmu_write_evtype(int idx, u32 val)
{
	armv8pmu_select_counter(idx);
	val &= ARMV8_PMU_EVTYPE_MASK;
	write_sysreg(val, pmxevtyper_el0);
}