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
 unsigned long GDROM_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  gdrom_is_busy () ; 
 int gdrom_wait_clrbusy () ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool gdrom_wait_busy_sleeps(void)
{
	unsigned long timeout;
	/* Wait to get busy first */
	timeout = jiffies + GDROM_DEFAULT_TIMEOUT;
	while (!gdrom_is_busy() && time_before(jiffies, timeout))
		cpu_relax();
	/* Now wait for busy to clear */
	return gdrom_wait_clrbusy();
}