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
 int /*<<< orphan*/  IPI_RESCHEDULE ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  send_ipi_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smp_send_reschedule(int cpu)
{
	send_ipi_message(cpumask_of(cpu), IPI_RESCHEDULE);
}