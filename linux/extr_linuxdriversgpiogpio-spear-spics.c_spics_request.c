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
typedef  int u32 ;
struct spear_spics {int sw_enable_bit; int cs_value_bit; scalar_t__ perip_cfg; scalar_t__ base; int /*<<< orphan*/  use_count; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct spear_spics* gpiochip_get_data (struct gpio_chip*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int spics_request(struct gpio_chip *chip, unsigned offset)
{
	struct spear_spics *spics = gpiochip_get_data(chip);
	u32 tmp;

	if (!spics->use_count++) {
		tmp = readl_relaxed(spics->base + spics->perip_cfg);
		tmp |= 0x1 << spics->sw_enable_bit;
		tmp |= 0x1 << spics->cs_value_bit;
		writel_relaxed(tmp, spics->base + spics->perip_cfg);
	}

	return 0;
}