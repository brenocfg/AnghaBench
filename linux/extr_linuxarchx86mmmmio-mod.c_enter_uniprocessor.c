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
 int num_online_cpus () ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static void enter_uniprocessor(void)
{
	if (num_online_cpus() > 1)
		pr_warning("multiple CPUs are online, may miss events. "
			   "Suggest booting with maxcpus=1 kernel argument.\n");
}