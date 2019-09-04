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
struct crystalcove_gpio {int /*<<< orphan*/  buslock; } ;

/* Variables and functions */
 struct crystalcove_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crystalcove_bus_lock(struct irq_data *data)
{
	struct crystalcove_gpio *cg =
		gpiochip_get_data(irq_data_get_irq_chip_data(data));

	mutex_lock(&cg->buslock);
}