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
 int /*<<< orphan*/  E500_PM_PH15 ; 
 int /*<<< orphan*/  rcpm_v1_cpu_exit_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcpm_v1_irq_unmask (int) ; 

__attribute__((used)) static void rcpm_v1_cpu_up_prepare(int cpu)
{
	rcpm_v1_cpu_exit_state(cpu, E500_PM_PH15);
	rcpm_v1_irq_unmask(cpu);
}