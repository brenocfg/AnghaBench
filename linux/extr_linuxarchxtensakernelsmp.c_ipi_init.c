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
 int /*<<< orphan*/  IPI_IRQ ; 
 int /*<<< orphan*/  ipi_irqaction ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_irq (unsigned int,int /*<<< orphan*/ *) ; 

void ipi_init(void)
{
	unsigned irq = irq_create_mapping(NULL, IPI_IRQ);
	setup_irq(irq, &ipi_irqaction);
}