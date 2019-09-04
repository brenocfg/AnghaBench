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
 int /*<<< orphan*/  ec_call_function_single ; 
 scalar_t__ pcpu_devices ; 
 int /*<<< orphan*/  pcpu_ec_call (scalar_t__,int /*<<< orphan*/ ) ; 

void arch_send_call_function_single_ipi(int cpu)
{
	pcpu_ec_call(pcpu_devices + cpu, ec_call_function_single);
}