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
 int ENODEV ; 
 int freeze_secondary_cpus (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ sleep_cpu ; 

int hibernate_resume_nonboot_cpu_disable(void)
{
	if (sleep_cpu < 0) {
		pr_err("Failing to resume from hibernate on an unknown CPU.\n");
		return -ENODEV;
	}

	return freeze_secondary_cpus(sleep_cpu);
}