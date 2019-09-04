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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP93XX_GPIO_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ IRQ_TYPE_EDGE_BOTH ; 
 int /*<<< orphan*/ * eoi_register_offset ; 
 int /*<<< orphan*/  ep93xx_gpio_update_int_params (int) ; 
 int* gpio_int_type2 ; 
 int* gpio_int_unmasked ; 
 int irq_to_gpio (int /*<<< orphan*/ ) ; 
 scalar_t__ irqd_get_trigger_type (struct irq_data*) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_gpio_irq_mask_ack(struct irq_data *d)
{
	int line = irq_to_gpio(d->irq);
	int port = line >> 3;
	int port_mask = 1 << (line & 7);

	if (irqd_get_trigger_type(d) == IRQ_TYPE_EDGE_BOTH)
		gpio_int_type2[port] ^= port_mask; /* switch edge direction */

	gpio_int_unmasked[port] &= ~port_mask;
	ep93xx_gpio_update_int_params(port);

	writeb(port_mask, EP93XX_GPIO_REG(eoi_register_offset[port]));
}