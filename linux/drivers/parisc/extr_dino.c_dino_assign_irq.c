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
struct dino_device {int* global_irq; } ;

/* Variables and functions */
 int NO_IRQ ; 
 int /*<<< orphan*/  dino_interrupt_type ; 
 int gsc_assign_irq (int /*<<< orphan*/ *,struct dino_device*) ; 

__attribute__((used)) static void dino_assign_irq(struct dino_device *dino, int local_irq, int *irqp)
{
	int irq = gsc_assign_irq(&dino_interrupt_type, dino);
	if (irq == NO_IRQ)
		return;

	*irqp = irq;
	dino->global_irq[local_irq] = irq;
}