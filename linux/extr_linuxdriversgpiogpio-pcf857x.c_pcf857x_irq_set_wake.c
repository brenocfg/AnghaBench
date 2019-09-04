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
struct pcf857x {scalar_t__ irq_parent; TYPE_1__* client; } ;
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct pcf857x* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irq_set_irq_wake (scalar_t__,unsigned int) ; 

__attribute__((used)) static int pcf857x_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct pcf857x *gpio = irq_data_get_irq_chip_data(data);

	int error = 0;

	if (gpio->irq_parent) {
		error = irq_set_irq_wake(gpio->irq_parent, on);
		if (error) {
			dev_dbg(&gpio->client->dev,
				"irq %u doesn't support irq_set_wake\n",
				gpio->irq_parent);
			gpio->irq_parent = 0;
		}
	}
	return error;
}