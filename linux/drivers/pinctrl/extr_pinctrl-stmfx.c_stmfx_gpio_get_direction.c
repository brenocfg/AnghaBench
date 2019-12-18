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
typedef  int u32 ;
struct stmfx_pinctrl {TYPE_1__* stmfx; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int STMFX_REG_GPIO_DIR ; 
 int get_mask (unsigned int) ; 
 int get_reg (unsigned int) ; 
 struct stmfx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int stmfx_gpio_get_direction(struct gpio_chip *gc, unsigned int offset)
{
	struct stmfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = STMFX_REG_GPIO_DIR + get_reg(offset);
	u32 mask = get_mask(offset);
	u32 val;
	int ret;

	ret = regmap_read(pctl->stmfx->map, reg, &val);
	/*
	 * On stmfx, gpio pins direction is (0)input, (1)output.
	 * .get_direction returns 0=out, 1=in
	 */

	return ret ? ret : !(val & mask);
}