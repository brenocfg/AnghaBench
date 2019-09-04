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
typedef  int /*<<< orphan*/  u8 ;
struct ingenic_gpio_chip {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ID_JZ4770 ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  JZ4740_GPIO_DIR ; 
 int /*<<< orphan*/  JZ4740_GPIO_TRIG ; 
 int /*<<< orphan*/  JZ4770_GPIO_PAT0 ; 
 int /*<<< orphan*/  JZ4770_GPIO_PAT1 ; 
 int /*<<< orphan*/  gpio_ingenic_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void irq_set_type(struct ingenic_gpio_chip *jzgc,
		u8 offset, unsigned int type)
{
	u8 reg1, reg2;

	if (jzgc->version >= ID_JZ4770) {
		reg1 = JZ4770_GPIO_PAT1;
		reg2 = JZ4770_GPIO_PAT0;
	} else {
		reg1 = JZ4740_GPIO_TRIG;
		reg2 = JZ4740_GPIO_DIR;
	}

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		gpio_ingenic_set_bit(jzgc, reg2, offset, true);
		gpio_ingenic_set_bit(jzgc, reg1, offset, true);
		break;
	case IRQ_TYPE_EDGE_FALLING:
		gpio_ingenic_set_bit(jzgc, reg2, offset, false);
		gpio_ingenic_set_bit(jzgc, reg1, offset, true);
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		gpio_ingenic_set_bit(jzgc, reg2, offset, true);
		gpio_ingenic_set_bit(jzgc, reg1, offset, false);
		break;
	case IRQ_TYPE_LEVEL_LOW:
	default:
		gpio_ingenic_set_bit(jzgc, reg2, offset, false);
		gpio_ingenic_set_bit(jzgc, reg1, offset, false);
		break;
	}
}