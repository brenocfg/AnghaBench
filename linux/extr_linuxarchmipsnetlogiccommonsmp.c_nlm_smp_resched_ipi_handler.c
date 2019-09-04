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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_c0_eirr (unsigned int) ; 
 int /*<<< orphan*/  clear_c0_eimr (unsigned int) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int /*<<< orphan*/  set_c0_eimr (unsigned int) ; 

void nlm_smp_resched_ipi_handler(struct irq_desc *desc)
{
	unsigned int irq = irq_desc_get_irq(desc);
	clear_c0_eimr(irq);
	ack_c0_eirr(irq);
	scheduler_ipi();
	set_c0_eimr(irq);
}