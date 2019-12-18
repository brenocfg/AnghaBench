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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 

__attribute__((used)) static void tqmx86_init_irq_valid_mask(struct gpio_chip *chip,
				       unsigned long *valid_mask,
				       unsigned int ngpios)
{
	/* Only GPIOs 4-7 are valid for interrupts. Clear the others */
	clear_bit(0, valid_mask);
	clear_bit(1, valid_mask);
	clear_bit(2, valid_mask);
	clear_bit(3, valid_mask);
}