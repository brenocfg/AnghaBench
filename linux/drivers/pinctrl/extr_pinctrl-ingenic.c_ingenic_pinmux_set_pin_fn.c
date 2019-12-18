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
struct ingenic_pinctrl {scalar_t__ version; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MSK ; 
 scalar_t__ ID_JZ4760 ; 
 scalar_t__ ID_X1000 ; 
 int /*<<< orphan*/  JZ4740_GPIO_FUNC ; 
 int /*<<< orphan*/  JZ4740_GPIO_SELECT ; 
 int /*<<< orphan*/  JZ4740_GPIO_TRIG ; 
 int /*<<< orphan*/  JZ4760_GPIO_INT ; 
 int /*<<< orphan*/  JZ4760_GPIO_PAT0 ; 
 int /*<<< orphan*/  JZ4760_GPIO_PAT1 ; 
 int PINS_PER_GPIO_CHIP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char,unsigned int,int) ; 
 int /*<<< orphan*/  ingenic_config_pin (struct ingenic_pinctrl*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ingenic_shadow_config_pin (struct ingenic_pinctrl*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ingenic_shadow_config_pin_load (struct ingenic_pinctrl*,int) ; 

__attribute__((used)) static int ingenic_pinmux_set_pin_fn(struct ingenic_pinctrl *jzpc,
		int pin, int func)
{
	unsigned int idx = pin % PINS_PER_GPIO_CHIP;
	unsigned int offt = pin / PINS_PER_GPIO_CHIP;

	dev_dbg(jzpc->dev, "set pin P%c%u to function %u\n",
			'A' + offt, idx, func);

	if (jzpc->version >= ID_X1000) {
		ingenic_shadow_config_pin(jzpc, pin, JZ4760_GPIO_INT, false);
		ingenic_shadow_config_pin(jzpc, pin, GPIO_MSK, false);
		ingenic_shadow_config_pin(jzpc, pin, JZ4760_GPIO_PAT1, func & 0x2);
		ingenic_shadow_config_pin(jzpc, pin, JZ4760_GPIO_PAT0, func & 0x1);
		ingenic_shadow_config_pin_load(jzpc, pin);
	} else if (jzpc->version >= ID_JZ4760) {
		ingenic_config_pin(jzpc, pin, JZ4760_GPIO_INT, false);
		ingenic_config_pin(jzpc, pin, GPIO_MSK, false);
		ingenic_config_pin(jzpc, pin, JZ4760_GPIO_PAT1, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4760_GPIO_PAT0, func & 0x1);
	} else {
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_FUNC, true);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_TRIG, func & 0x2);
		ingenic_config_pin(jzpc, pin, JZ4740_GPIO_SELECT, func > 0);
	}

	return 0;
}