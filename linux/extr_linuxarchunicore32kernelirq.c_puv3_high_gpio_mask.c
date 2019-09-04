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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_GFER ; 
 int /*<<< orphan*/  GPIO_GRER ; 
 unsigned int GPIO_IRQ_mask ; 
 unsigned int GPIO_MASK (int /*<<< orphan*/ ) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puv3_high_gpio_mask(struct irq_data *d)
{
	unsigned int mask = GPIO_MASK(d->irq);

	GPIO_IRQ_mask &= ~mask;

	writel(readl(GPIO_GRER) & ~mask, GPIO_GRER);
	writel(readl(GPIO_GFER) & ~mask, GPIO_GFER);
}