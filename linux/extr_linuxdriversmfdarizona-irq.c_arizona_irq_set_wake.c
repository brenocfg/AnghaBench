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
struct arizona {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct arizona* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_set_irq_wake (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int arizona_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct arizona *arizona = irq_data_get_irq_chip_data(data);

	return irq_set_irq_wake(arizona->irq, on);
}