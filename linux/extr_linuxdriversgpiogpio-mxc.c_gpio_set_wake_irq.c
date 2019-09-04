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
typedef  int u32 ;
struct mxc_gpio_port {scalar_t__ irq; scalar_t__ irq_high; } ;
struct irq_data {int hwirq; } ;
struct irq_chip_generic {struct mxc_gpio_port* private; } ;

/* Variables and functions */
 int disable_irq_wake (scalar_t__) ; 
 int enable_irq_wake (scalar_t__) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int gpio_set_wake_irq(struct irq_data *d, u32 enable)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(d);
	struct mxc_gpio_port *port = gc->private;
	u32 gpio_idx = d->hwirq;
	int ret;

	if (enable) {
		if (port->irq_high && (gpio_idx >= 16))
			ret = enable_irq_wake(port->irq_high);
		else
			ret = enable_irq_wake(port->irq);
	} else {
		if (port->irq_high && (gpio_idx >= 16))
			ret = disable_irq_wake(port->irq_high);
		else
			ret = disable_irq_wake(port->irq);
	}

	return ret;
}