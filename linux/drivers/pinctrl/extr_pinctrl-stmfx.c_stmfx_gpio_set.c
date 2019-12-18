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
typedef  scalar_t__ u32 ;
struct stmfx_pinctrl {TYPE_1__* stmfx; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 scalar_t__ STMFX_REG_GPO_CLR ; 
 scalar_t__ STMFX_REG_GPO_SET ; 
 scalar_t__ get_mask (unsigned int) ; 
 scalar_t__ get_reg (unsigned int) ; 
 struct stmfx_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void stmfx_gpio_set(struct gpio_chip *gc, unsigned int offset, int value)
{
	struct stmfx_pinctrl *pctl = gpiochip_get_data(gc);
	u32 reg = value ? STMFX_REG_GPO_SET : STMFX_REG_GPO_CLR;
	u32 mask = get_mask(offset);

	regmap_write_bits(pctl->stmfx->map, reg + get_reg(offset),
			  mask, mask);
}