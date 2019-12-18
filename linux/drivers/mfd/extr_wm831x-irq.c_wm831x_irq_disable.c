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
struct wm831x_irq_data {int reg; int /*<<< orphan*/  mask; } ;
struct wm831x {int /*<<< orphan*/ * irq_masks_cur; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 struct wm831x* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct wm831x_irq_data* irq_to_wm831x_irq (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm831x_irq_disable(struct irq_data *data)
{
	struct wm831x *wm831x = irq_data_get_irq_chip_data(data);
	struct wm831x_irq_data *irq_data = irq_to_wm831x_irq(wm831x,
							     data->hwirq);

	wm831x->irq_masks_cur[irq_data->reg - 1] |= irq_data->mask;
}