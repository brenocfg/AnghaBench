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
struct gpio {int dummy; } ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;

/* Variables and functions */
 scalar_t__ DC_IRQ_SOURCE_HPD1RX ; 
 int DC_IRQ_SOURCE_INVALID ; 
#define  GPIO_ID_HPD 128 
 scalar_t__ dal_gpio_get_enum (struct gpio const*) ; 
 int dal_gpio_get_id (struct gpio const*) ; 

enum dc_irq_source dal_irq_get_rx_source(
	const struct gpio *irq)
{
	enum gpio_id id = dal_gpio_get_id(irq);

	switch (id) {
	case GPIO_ID_HPD:
		return (enum dc_irq_source)(DC_IRQ_SOURCE_HPD1RX +
			dal_gpio_get_enum(irq));
	default:
		return DC_IRQ_SOURCE_INVALID;
	}
}