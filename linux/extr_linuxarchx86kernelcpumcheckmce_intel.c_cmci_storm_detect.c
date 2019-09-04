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
 unsigned int CMCI_STORM_ACTIVE ; 
 scalar_t__ CMCI_STORM_INTERVAL ; 
 void* CMCI_STORM_NONE ; 
 unsigned int CMCI_STORM_THRESHOLD ; 
 int /*<<< orphan*/  INITIAL_CHECK_INTERVAL ; 
 void* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmci_backoff_cnt ; 
 int /*<<< orphan*/  cmci_storm_cnt ; 
 int /*<<< orphan*/  cmci_storm_on_cpus ; 
 int /*<<< orphan*/  cmci_storm_state ; 
 int /*<<< orphan*/  cmci_time_stamp ; 
 int /*<<< orphan*/  cmci_toggle_interrupt_mode (int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mce_timer_kick (scalar_t__) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before_eq (unsigned long,scalar_t__) ; 

__attribute__((used)) static bool cmci_storm_detect(void)
{
	unsigned int cnt = __this_cpu_read(cmci_storm_cnt);
	unsigned long ts = __this_cpu_read(cmci_time_stamp);
	unsigned long now = jiffies;
	int r;

	if (__this_cpu_read(cmci_storm_state) != CMCI_STORM_NONE)
		return true;

	if (time_before_eq(now, ts + CMCI_STORM_INTERVAL)) {
		cnt++;
	} else {
		cnt = 1;
		__this_cpu_write(cmci_time_stamp, now);
	}
	__this_cpu_write(cmci_storm_cnt, cnt);

	if (cnt <= CMCI_STORM_THRESHOLD)
		return false;

	cmci_toggle_interrupt_mode(false);
	__this_cpu_write(cmci_storm_state, CMCI_STORM_ACTIVE);
	r = atomic_add_return(1, &cmci_storm_on_cpus);
	mce_timer_kick(CMCI_STORM_INTERVAL);
	this_cpu_write(cmci_backoff_cnt, INITIAL_CHECK_INTERVAL);

	if (r == 1)
		pr_notice("CMCI storm detected: switching to poll mode\n");
	return true;
}