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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 size_t PSCI_FN_CPU_SUSPEND ; 
 int invoke_psci_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * psci_function_id ; 
 int psci_to_linux_errno (int) ; 

__attribute__((used)) static int psci_cpu_suspend(u32 state, unsigned long entry_point)
{
	int err;
	u32 fn;

	fn = psci_function_id[PSCI_FN_CPU_SUSPEND];
	err = invoke_psci_fn(fn, state, entry_point, 0);
	return psci_to_linux_errno(err);
}