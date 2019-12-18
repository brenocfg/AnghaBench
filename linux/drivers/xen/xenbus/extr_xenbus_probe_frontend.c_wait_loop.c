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
 unsigned int HZ ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (unsigned int) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool wait_loop(unsigned long start, unsigned int max_delay,
		     unsigned int *seconds_waited)
{
	if (time_after(jiffies, start + (*seconds_waited+5)*HZ)) {
		if (!*seconds_waited)
			pr_warn("Waiting for devices to initialise: ");
		*seconds_waited += 5;
		pr_cont("%us...", max_delay - *seconds_waited);
		if (*seconds_waited == max_delay) {
			pr_cont("\n");
			return true;
		}
	}

	schedule_timeout_interruptible(HZ/10);

	return false;
}