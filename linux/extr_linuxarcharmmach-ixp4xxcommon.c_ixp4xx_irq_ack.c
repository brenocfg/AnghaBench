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
 int* IXP4XX_GPIO_GPISR ; 
 int* irq2gpio ; 

__attribute__((used)) static void ixp4xx_irq_ack(struct irq_data *d)
{
	int line = (d->irq < 32) ? irq2gpio[d->irq] : -1;

	if (line >= 0)
		*IXP4XX_GPIO_GPISR = (1 << line);
}