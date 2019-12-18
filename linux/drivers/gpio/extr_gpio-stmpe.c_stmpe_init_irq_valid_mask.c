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
typedef  int /*<<< orphan*/  u32 ;
struct stmpe_gpio {int norequest_mask; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static void stmpe_init_irq_valid_mask(struct gpio_chip *gc,
				      unsigned long *valid_mask,
				      unsigned int ngpios)
{
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(gc);
	int i;

	if (!stmpe_gpio->norequest_mask)
		return;

	/* Forbid unused lines to be mapped as IRQs */
	for (i = 0; i < sizeof(u32); i++) {
		if (stmpe_gpio->norequest_mask & BIT(i))
			clear_bit(i, valid_mask);
	}
}