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
 int /*<<< orphan*/  PM_PWER ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_low_gpio_wake(struct irq_data *d, unsigned int on)
{
	if (on)
		writel(readl(PM_PWER) | (1 << d->irq), PM_PWER);
	else
		writel(readl(PM_PWER) & ~(1 << d->irq), PM_PWER);
	return 0;
}