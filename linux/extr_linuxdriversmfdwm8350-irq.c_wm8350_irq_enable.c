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
struct wm8350_irq_data {size_t reg; int /*<<< orphan*/  mask; } ;
struct wm8350 {int /*<<< orphan*/ * irq_masks; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct wm8350* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct wm8350_irq_data* irq_to_wm8350_irq (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8350_irq_enable(struct irq_data *data)
{
	struct wm8350 *wm8350 = irq_data_get_irq_chip_data(data);
	struct wm8350_irq_data *irq_data = irq_to_wm8350_irq(wm8350,
							     data->irq);

	wm8350->irq_masks[irq_data->reg] &= ~irq_data->mask;
}