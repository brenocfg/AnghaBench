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
struct irq_data {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_MCLR ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ebsa110_mask_irq(struct irq_data *d)
{
	__raw_writeb(1 << d->irq, IRQ_MCLR);
}