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
typedef  unsigned int u32 ;
struct spear_spics {unsigned int last_off; unsigned int cs_enable_mask; unsigned int cs_enable_shift; int cs_value_bit; scalar_t__ perip_cfg; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct spear_spics* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void spics_set_value(struct gpio_chip *chip, unsigned offset, int value)
{
	struct spear_spics *spics = gpiochip_get_data(chip);
	u32 tmp;

	/* select chip select from register */
	tmp = readl_relaxed(spics->base + spics->perip_cfg);
	if (spics->last_off != offset) {
		spics->last_off = offset;
		tmp &= ~(spics->cs_enable_mask << spics->cs_enable_shift);
		tmp |= offset << spics->cs_enable_shift;
	}

	/* toggle chip select line */
	tmp &= ~(0x1 << spics->cs_value_bit);
	tmp |= value << spics->cs_value_bit;
	writel_relaxed(tmp, spics->base + spics->perip_cfg);
}