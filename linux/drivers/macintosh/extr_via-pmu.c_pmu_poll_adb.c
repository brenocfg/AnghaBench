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

/* Variables and functions */
 int adb_int_pending ; 
 scalar_t__ disable_poll ; 
 scalar_t__ idle ; 
 scalar_t__ pmu_state ; 
 scalar_t__ pmu_suspended ; 
 scalar_t__ req_awaiting_reply ; 
 scalar_t__ uninitialized ; 
 int /*<<< orphan*/  via_pmu_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
pmu_poll_adb(void)
{
	if (pmu_state == uninitialized)
		return;
	if (disable_poll)
		return;
	/* Kicks ADB read when PMU is suspended */
	adb_int_pending = 1;
	do {
		via_pmu_interrupt(0, NULL);
	} while (pmu_suspended && (adb_int_pending || pmu_state != idle
		|| req_awaiting_reply));
}