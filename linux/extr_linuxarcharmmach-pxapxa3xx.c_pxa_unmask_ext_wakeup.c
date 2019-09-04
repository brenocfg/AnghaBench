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
struct irq_data {scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ IRQ_WAKEUP0 ; 
 int /*<<< orphan*/  PECR ; 
 int /*<<< orphan*/  PECR_IE (scalar_t__) ; 
 int /*<<< orphan*/  pxa_unmask_irq (struct irq_data*) ; 

__attribute__((used)) static void pxa_unmask_ext_wakeup(struct irq_data *d)
{
	pxa_unmask_irq(d);
	PECR |= PECR_IE(d->irq - IRQ_WAKEUP0);
}