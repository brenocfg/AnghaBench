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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int NR_IPI ; 
 scalar_t__ __get_irq_stat (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipi_irqs ; 

u64 smp_irq_stat_cpu(unsigned int cpu)
{
	u64 sum = 0;
	int i;

	for (i = 0; i < NR_IPI; i++)
		sum += __get_irq_stat(cpu, ipi_irqs[i]);

	return sum;
}