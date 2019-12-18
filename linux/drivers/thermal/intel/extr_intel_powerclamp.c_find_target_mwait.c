#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cpuid_level; } ;

/* Variables and functions */
 unsigned int CPUID5_ECX_EXTENSIONS_SUPPORTED ; 
 unsigned int CPUID5_ECX_INTERRUPT_BREAK ; 
 scalar_t__ CPUID_MWAIT_LEAF ; 
 unsigned int MWAIT_SUBSTATE_MASK ; 
 unsigned int MWAIT_SUBSTATE_SIZE ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid (scalar_t__,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 unsigned int target_mwait ; 

__attribute__((used)) static void find_target_mwait(void)
{
	unsigned int eax, ebx, ecx, edx;
	unsigned int highest_cstate = 0;
	unsigned int highest_subcstate = 0;
	int i;

	if (boot_cpu_data.cpuid_level < CPUID_MWAIT_LEAF)
		return;

	cpuid(CPUID_MWAIT_LEAF, &eax, &ebx, &ecx, &edx);

	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPORTED) ||
	    !(ecx & CPUID5_ECX_INTERRUPT_BREAK))
		return;

	edx >>= MWAIT_SUBSTATE_SIZE;
	for (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) {
		if (edx & MWAIT_SUBSTATE_MASK) {
			highest_cstate = i;
			highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
		}
	}
	target_mwait = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
		(highest_subcstate - 1);

}