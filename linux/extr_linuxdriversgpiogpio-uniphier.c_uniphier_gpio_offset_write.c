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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uniphier_gpio_bank_write (struct gpio_chip*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_gpio_get_bank_and_mask (unsigned int,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uniphier_gpio_offset_write(struct gpio_chip *chip,
				       unsigned int offset, unsigned int reg,
				       int val)
{
	unsigned int bank;
	u32 mask;

	uniphier_gpio_get_bank_and_mask(offset, &bank, &mask);

	uniphier_gpio_bank_write(chip, bank, reg, mask, val ? mask : 0);
}