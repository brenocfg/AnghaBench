#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct mtk_pinctrl {int /*<<< orphan*/  eint; TYPE_1__* soc; } ;
struct TYPE_4__ {scalar_t__ eint_n; } ;
struct mtk_pin_desc {TYPE_2__ eint; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pins; } ;

/* Variables and functions */
 scalar_t__ EINT_NA ; 
 int ENOTSUPP ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int mtk_eint_find_irq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mtk_gpio_to_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct mtk_pinctrl *hw = gpiochip_get_data(chip);
	const struct mtk_pin_desc *desc;

	if (!hw->eint)
		return -ENOTSUPP;

	desc = (const struct mtk_pin_desc *)&hw->soc->pins[offset];

	if (desc->eint.eint_n == (u16)EINT_NA)
		return -ENOTSUPP;

	return mtk_eint_find_irq(hw->eint, desc->eint.eint_n);
}