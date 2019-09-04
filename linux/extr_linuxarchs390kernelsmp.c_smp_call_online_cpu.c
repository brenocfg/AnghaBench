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
struct pcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_delegate (struct pcpu*,void (*) (void*),void*,unsigned long) ; 
 struct pcpu* pcpu_devices ; 
 struct pcpu* pcpu_find_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ restart_stack ; 
 int /*<<< orphan*/  stap () ; 

void smp_call_online_cpu(void (*func)(void *), void *data)
{
	struct pcpu *pcpu;

	/* Use the current cpu if it is online. */
	pcpu = pcpu_find_address(cpu_online_mask, stap());
	if (!pcpu)
		/* Use the first online cpu. */
		pcpu = pcpu_devices + cpumask_first(cpu_online_mask);
	pcpu_delegate(pcpu, func, data, (unsigned long) restart_stack);
}