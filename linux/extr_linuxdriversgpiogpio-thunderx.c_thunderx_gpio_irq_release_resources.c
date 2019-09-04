#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thunderx_line {int /*<<< orphan*/  line; struct thunderx_gpio* txgpio; } ;
struct thunderx_gpio {int /*<<< orphan*/  chip; } ;
struct irq_data {TYPE_1__* chip; struct irq_data* parent_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_release_resources ) (struct irq_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_unlock_as_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct thunderx_line* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  stub1 (struct irq_data*) ; 

__attribute__((used)) static void thunderx_gpio_irq_release_resources(struct irq_data *data)
{
	struct thunderx_line *txline = irq_data_get_irq_chip_data(data);
	struct thunderx_gpio *txgpio = txline->txgpio;
	struct irq_data *parent_data = data->parent_data;

	if (parent_data && parent_data->chip->irq_release_resources)
		parent_data->chip->irq_release_resources(parent_data);

	gpiochip_unlock_as_irq(&txgpio->chip, txline->line);
}