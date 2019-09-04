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
struct TYPE_2__ {int (* irq_request_resources ) (struct irq_data*) ;} ;

/* Variables and functions */
 int gpiochip_lock_as_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_unlock_as_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct thunderx_line* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int stub1 (struct irq_data*) ; 

__attribute__((used)) static int thunderx_gpio_irq_request_resources(struct irq_data *data)
{
	struct thunderx_line *txline = irq_data_get_irq_chip_data(data);
	struct thunderx_gpio *txgpio = txline->txgpio;
	struct irq_data *parent_data = data->parent_data;
	int r;

	r = gpiochip_lock_as_irq(&txgpio->chip, txline->line);
	if (r)
		return r;

	if (parent_data && parent_data->chip->irq_request_resources) {
		r = parent_data->chip->irq_request_resources(parent_data);
		if (r)
			goto error;
	}

	return 0;
error:
	gpiochip_unlock_as_irq(&txgpio->chip, txline->line);
	return r;
}