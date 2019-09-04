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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  altera_gpio_irq_unmask (struct irq_data*) ; 

__attribute__((used)) static unsigned int altera_gpio_irq_startup(struct irq_data *d)
{
	altera_gpio_irq_unmask(d);

	return 0;
}