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
typedef  int /*<<< orphan*/  u8 ;
struct ingenic_gpio_chip {TYPE_1__* jzpc; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4760 ; 
 scalar_t__ ID_X1000 ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  JZ4740_GPIO_DIR ; 
 int /*<<< orphan*/  JZ4740_GPIO_TRIG ; 
 int /*<<< orphan*/  JZ4760_GPIO_PAT0 ; 
 int /*<<< orphan*/  JZ4760_GPIO_PAT1 ; 
 int /*<<< orphan*/  ingenic_gpio_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ingenic_gpio_shadow_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ingenic_gpio_shadow_set_bit_load (struct ingenic_gpio_chip*) ; 

__attribute__((used)) static void irq_set_type(struct ingenic_gpio_chip *jzgc,
		u8 offset, unsigned int type)
{
	u8 reg1, reg2;

	if (jzgc->jzpc->version >= ID_JZ4760) {
		reg1 = JZ4760_GPIO_PAT1;
		reg2 = JZ4760_GPIO_PAT0;
	} else {
		reg1 = JZ4740_GPIO_TRIG;
		reg2 = JZ4740_GPIO_DIR;
	}

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		if (jzgc->jzpc->version >= ID_X1000) {
			ingenic_gpio_shadow_set_bit(jzgc, reg2, offset, true);
			ingenic_gpio_shadow_set_bit(jzgc, reg1, offset, true);
			ingenic_gpio_shadow_set_bit_load(jzgc);
		} else {
			ingenic_gpio_set_bit(jzgc, reg2, offset, true);
			ingenic_gpio_set_bit(jzgc, reg1, offset, true);
		}
		break;
	case IRQ_TYPE_EDGE_FALLING:
		if (jzgc->jzpc->version >= ID_X1000) {
			ingenic_gpio_shadow_set_bit(jzgc, reg2, offset, false);
			ingenic_gpio_shadow_set_bit(jzgc, reg1, offset, true);
			ingenic_gpio_shadow_set_bit_load(jzgc);
		} else {
			ingenic_gpio_set_bit(jzgc, reg2, offset, false);
			ingenic_gpio_set_bit(jzgc, reg1, offset, true);
		}
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		if (jzgc->jzpc->version >= ID_X1000) {
			ingenic_gpio_shadow_set_bit(jzgc, reg2, offset, true);
			ingenic_gpio_shadow_set_bit(jzgc, reg1, offset, false);
			ingenic_gpio_shadow_set_bit_load(jzgc);
		} else {
			ingenic_gpio_set_bit(jzgc, reg2, offset, true);
			ingenic_gpio_set_bit(jzgc, reg1, offset, false);
		}
		break;
	case IRQ_TYPE_LEVEL_LOW:
	default:
		if (jzgc->jzpc->version >= ID_X1000) {
			ingenic_gpio_shadow_set_bit(jzgc, reg2, offset, false);
			ingenic_gpio_shadow_set_bit(jzgc, reg1, offset, false);
			ingenic_gpio_shadow_set_bit_load(jzgc);
		} else {
			ingenic_gpio_set_bit(jzgc, reg2, offset, false);
			ingenic_gpio_set_bit(jzgc, reg1, offset, false);
		}
		break;
	}
}