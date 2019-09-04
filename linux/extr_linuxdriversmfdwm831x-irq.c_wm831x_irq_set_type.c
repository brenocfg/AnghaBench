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
struct wm831x {int* gpio_level_low; int* gpio_level_high; int* gpio_update; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int WM831X_GPN_INT_MODE ; 
 int WM831X_GPN_POL ; 
 int WM831X_IRQ_GPIO_1 ; 
 int WM831X_IRQ_GPIO_11 ; 
 int WM831X_NUM_IRQS ; 
 struct wm831x* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int wm831x_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct wm831x *wm831x = irq_data_get_irq_chip_data(data);
	int irq;

	irq = data->hwirq;

	if (irq < WM831X_IRQ_GPIO_1 || irq > WM831X_IRQ_GPIO_11) {
		/* Ignore internal-only IRQs */
		if (irq >= 0 && irq < WM831X_NUM_IRQS)
			return 0;
		else
			return -EINVAL;
	}

	/* Rebase the IRQ into the GPIO range so we've got a sensible array
	 * index.
	 */
	irq -= WM831X_IRQ_GPIO_1;

	/* We set the high bit to flag that we need an update; don't
	 * do the update here as we can be called with the bus lock
	 * held.
	 */
	wm831x->gpio_level_low[irq] = false;
	wm831x->gpio_level_high[irq] = false;
	switch (type) {
	case IRQ_TYPE_EDGE_BOTH:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_INT_MODE;
		break;
	case IRQ_TYPE_EDGE_RISING:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_POL;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		wm831x->gpio_update[irq] = 0x10000;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		wm831x->gpio_update[irq] = 0x10000 | WM831X_GPN_POL;
		wm831x->gpio_level_high[irq] = true;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		wm831x->gpio_update[irq] = 0x10000;
		wm831x->gpio_level_low[irq] = true;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}