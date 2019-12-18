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
struct gpio_desc {scalar_t__ label; int /*<<< orphan*/  flags; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_IRQ_IS_ENABLED ; 
 int /*<<< orphan*/  FLAG_USED_AS_IRQ ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  desc_set_label (struct gpio_desc*,int /*<<< orphan*/ *) ; 
 struct gpio_desc* gpiochip_get_desc (struct gpio_chip*,unsigned int) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

void gpiochip_unlock_as_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct gpio_desc *desc;

	desc = gpiochip_get_desc(chip, offset);
	if (IS_ERR(desc))
		return;

	clear_bit(FLAG_USED_AS_IRQ, &desc->flags);
	clear_bit(FLAG_IRQ_IS_ENABLED, &desc->flags);

	/* If we only had this marking, erase it */
	if (desc->label && !strcmp(desc->label, "interrupt"))
		desc_set_label(desc, NULL);
}