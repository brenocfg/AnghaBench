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
 int /*<<< orphan*/  CVMX_CIU_SOFT_RST ; 
 int /*<<< orphan*/  CVMX_CIU_WDOGX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_RST_SOFT_RST ; 
 scalar_t__ OCTEON_IS_OCTEON3 () ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void octeon_restart(char *command)
{
	/* Disable all watchdogs before soft reset. They don't get cleared */
#ifdef CONFIG_SMP
	int cpu;
	for_each_online_cpu(cpu)
		cvmx_write_csr(CVMX_CIU_WDOGX(cpu_logical_map(cpu)), 0);
#else
	cvmx_write_csr(CVMX_CIU_WDOGX(cvmx_get_core_num()), 0);
#endif

	mb();
	while (1)
		if (OCTEON_IS_OCTEON3())
			cvmx_write_csr(CVMX_RST_SOFT_RST, 1);
		else
			cvmx_write_csr(CVMX_CIU_SOFT_RST, 1);
}