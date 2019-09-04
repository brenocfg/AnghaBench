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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_TIME_REF_COUNT ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 read_hv_clock_msr(struct clocksource *arg)
{
	u64 current_tick;
	/*
	 * Read the partition counter to get the current tick count. This count
	 * is set to 0 when the partition is created and is incremented in
	 * 100 nanosecond units.
	 */
	rdmsrl(HV_X64_MSR_TIME_REF_COUNT, current_tick);
	return current_tick;
}