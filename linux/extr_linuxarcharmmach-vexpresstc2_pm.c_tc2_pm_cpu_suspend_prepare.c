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
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpm_entry_point ; 
 int /*<<< orphan*/  ve_spc_set_resume_addr (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc2_pm_cpu_suspend_prepare(unsigned int cpu, unsigned int cluster)
{
	ve_spc_set_resume_addr(cluster, cpu, __pa_symbol(mcpm_entry_point));
}