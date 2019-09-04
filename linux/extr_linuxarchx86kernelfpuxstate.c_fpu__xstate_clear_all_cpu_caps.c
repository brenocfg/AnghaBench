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
 int /*<<< orphan*/  X86_FEATURE_XSAVE ; 
 int /*<<< orphan*/  setup_clear_cpu_cap (int /*<<< orphan*/ ) ; 

void fpu__xstate_clear_all_cpu_caps(void)
{
	setup_clear_cpu_cap(X86_FEATURE_XSAVE);
}