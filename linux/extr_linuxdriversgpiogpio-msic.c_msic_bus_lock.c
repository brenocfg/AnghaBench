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
struct msic_gpio {int /*<<< orphan*/  buslock; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct msic_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msic_bus_lock(struct irq_data *data)
{
	struct msic_gpio *mg = irq_data_get_irq_chip_data(data);
	mutex_lock(&mg->buslock);
}