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
 int EINVAL ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_NO_THREAD ; 
 int IRQF_PERCPU ; 
 int PPC_MSG_NMI_IPI ; 
 int /*<<< orphan*/  WARN (int,char*,int,int /*<<< orphan*/ ,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * smp_ipi_action ; 
 int /*<<< orphan*/ * smp_ipi_name ; 

int smp_request_message_ipi(int virq, int msg)
{
	int err;

	if (msg < 0 || msg > PPC_MSG_NMI_IPI)
		return -EINVAL;
#ifndef CONFIG_NMI_IPI
	if (msg == PPC_MSG_NMI_IPI)
		return 1;
#endif

	err = request_irq(virq, smp_ipi_action[msg],
			  IRQF_PERCPU | IRQF_NO_THREAD | IRQF_NO_SUSPEND,
			  smp_ipi_name[msg], NULL);
	WARN(err < 0, "unable to request_irq %d for %s (rc %d)\n",
		virq, smp_ipi_name[msg], err);

	return err;
}