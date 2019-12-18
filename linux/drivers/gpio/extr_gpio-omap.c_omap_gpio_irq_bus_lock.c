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
struct irq_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct gpio_bank {TYPE_1__ chip; } ;

/* Variables and functions */
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_gpio_irq_bus_lock(struct irq_data *data)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(data);

	pm_runtime_get_sync(bank->chip.parent);
}