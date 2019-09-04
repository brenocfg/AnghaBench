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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static unsigned int longrun_get(unsigned int cpu)
{
	u32 eax, ebx, ecx, edx;

	if (cpu)
		return 0;

	cpuid(0x80860007, &eax, &ebx, &ecx, &edx);
	pr_debug("cpuid eax is %u\n", eax);

	return eax * 1000;
}