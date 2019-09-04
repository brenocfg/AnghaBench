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
 int /*<<< orphan*/  MSIC_GPIO_DOUT_MASK ; 
 int /*<<< orphan*/  intel_msic_reg_update (int,int,int /*<<< orphan*/ ) ; 
 int msic_gpio_to_oreg (unsigned int) ; 

__attribute__((used)) static void msic_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	int reg;

	reg = msic_gpio_to_oreg(offset);
	if (reg < 0)
		return;

	intel_msic_reg_update(reg, !!value , MSIC_GPIO_DOUT_MASK);
}