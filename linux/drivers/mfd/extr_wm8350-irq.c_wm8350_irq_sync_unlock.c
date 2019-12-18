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
struct wm8350 {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * irq_masks; int /*<<< orphan*/  regmap; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WM8350_INT_STATUS_1_MASK ; 
 struct wm8350* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8350_irq_sync_unlock(struct irq_data *data)
{
	struct wm8350 *wm8350 = irq_data_get_irq_chip_data(data);
	int i;

	for (i = 0; i < ARRAY_SIZE(wm8350->irq_masks); i++) {
		/* If there's been a change in the mask write it back
		 * to the hardware. */
		WARN_ON(regmap_update_bits(wm8350->regmap,
					   WM8350_INT_STATUS_1_MASK + i,
					   0xffff, wm8350->irq_masks[i]));
	}

	mutex_unlock(&wm8350->irq_lock);
}