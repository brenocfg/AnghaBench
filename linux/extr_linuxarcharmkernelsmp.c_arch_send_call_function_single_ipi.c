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
 int /*<<< orphan*/  IPI_CALL_FUNC ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  smp_cross_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arch_send_call_function_single_ipi(int cpu)
{
	smp_cross_call(cpumask_of(cpu), IPI_CALL_FUNC);
}