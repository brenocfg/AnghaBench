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
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_unlock_as_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_giuint_low (struct irq_data*) ; 
 int /*<<< orphan*/  vr41xx_gpio_chip ; 

__attribute__((used)) static void shutdown_giuint(struct irq_data *data)
{
	mask_giuint_low(data);
	gpiochip_unlock_as_irq(&vr41xx_gpio_chip, data->hwirq);
}