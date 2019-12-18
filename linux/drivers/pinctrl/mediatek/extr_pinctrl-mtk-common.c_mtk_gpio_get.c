#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_pinctrl {int /*<<< orphan*/  regmap1; TYPE_1__* devdata; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {unsigned int din_offset; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 struct mtk_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int mtk_get_port (struct mtk_pinctrl*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int mtk_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	unsigned int reg_addr;
	unsigned int bit;
	unsigned int read_val = 0;
	struct mtk_pinctrl *pctl = gpiochip_get_data(chip);

	reg_addr = mtk_get_port(pctl, offset) +
		pctl->devdata->din_offset;

	bit = BIT(offset & 0xf);
	regmap_read(pctl->regmap1, reg_addr, &read_val);
	return !!(read_val & bit);
}