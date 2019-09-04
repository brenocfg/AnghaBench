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
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_online (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void panic_smp_self_stop(void)
{
	pr_debug("CPU %u will stop doing anything useful since another CPU has paniced\n",
	         smp_processor_id());
	set_cpu_online(smp_processor_id(), false);
	while (1)
		cpu_relax();
}