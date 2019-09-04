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
 int /*<<< orphan*/  CPU_FTR_ARCH_207S ; 
 int /*<<< orphan*/  CPU_FTR_DAWR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

bool ppc_breakpoint_available(void)
{
	if (cpu_has_feature(CPU_FTR_DAWR))
		return true; /* POWER8 DAWR */
	if (cpu_has_feature(CPU_FTR_ARCH_207S))
		return false; /* POWER9 with DAWR disabled */
	/* DABR: Everything but POWER8 and POWER9 */
	return true;
}