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
 int /*<<< orphan*/  MCFSIM2_GPIOINTCLEAR ; 
 int MCF_IRQ_GPIO0 ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intc2_irq_gpio_ack(struct irq_data *d)
{
	writel(0x1 << (d->irq - MCF_IRQ_GPIO0), MCFSIM2_GPIOINTCLEAR);
}