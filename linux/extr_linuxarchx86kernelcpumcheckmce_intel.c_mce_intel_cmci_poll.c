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
 scalar_t__ CMCI_STORM_NONE ; 
 int /*<<< orphan*/  INITIAL_CHECK_INTERVAL ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmci_backoff_cnt ; 
 int /*<<< orphan*/  cmci_storm_state ; 
 scalar_t__ machine_check_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool mce_intel_cmci_poll(void)
{
	if (__this_cpu_read(cmci_storm_state) == CMCI_STORM_NONE)
		return false;

	/*
	 * Reset the counter if we've logged an error in the last poll
	 * during the storm.
	 */
	if (machine_check_poll(0, this_cpu_ptr(&mce_banks_owned)))
		this_cpu_write(cmci_backoff_cnt, INITIAL_CHECK_INTERVAL);
	else
		this_cpu_dec(cmci_backoff_cnt);

	return true;
}