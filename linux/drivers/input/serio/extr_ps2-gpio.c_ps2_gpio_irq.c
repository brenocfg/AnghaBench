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
struct ps2_gpio_data {scalar_t__ mode; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ps2_gpio_irq_rx (struct ps2_gpio_data*) ; 
 int /*<<< orphan*/  ps2_gpio_irq_tx (struct ps2_gpio_data*) ; 

__attribute__((used)) static irqreturn_t ps2_gpio_irq(int irq, void *dev_id)
{
	struct ps2_gpio_data *drvdata = dev_id;

	return drvdata->mode ? ps2_gpio_irq_tx(drvdata) :
		ps2_gpio_irq_rx(drvdata);
}