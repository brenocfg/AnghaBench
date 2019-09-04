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
 int /*<<< orphan*/  XSTATE_CPUID ; 
 int /*<<< orphan*/  cpuid_count (int /*<<< orphan*/ ,int,int*,int*,int*,int*) ; 

__attribute__((used)) static int xfeature_is_supervisor(int xfeature_nr)
{
	/*
	 * We currently do not support supervisor states, but if
	 * we did, we could find out like this.
	 *
	 * SDM says: If state component 'i' is a user state component,
	 * ECX[0] return 0; if state component i is a supervisor
	 * state component, ECX[0] returns 1.
	 */
	u32 eax, ebx, ecx, edx;

	cpuid_count(XSTATE_CPUID, xfeature_nr, &eax, &ebx, &ecx, &edx);
	return !!(ecx & 1);
}