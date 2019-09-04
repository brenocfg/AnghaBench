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
struct irq_chip {int dummy; } ;
struct irq_chip_type {struct irq_chip chip; } ;

/* Variables and functions */
 struct irq_chip_type* irq_data_get_chip_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 

__attribute__((used)) static struct irq_chip *davinci_gpio_get_irq_chip(unsigned int irq)
{
	static struct irq_chip_type gpio_unbanked;

	gpio_unbanked = *irq_data_get_chip_type(irq_get_irq_data(irq));

	return &gpio_unbanked.chip;
}