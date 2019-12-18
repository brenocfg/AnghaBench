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
 int /*<<< orphan*/  JZ4740_GPIO_DATA ; 
 int /*<<< orphan*/  JZ4760_GPIO_PAT0 ; 
 int /*<<< orphan*/  ingenic_gpio_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ingenic_gpio_set_value(struct ingenic_gpio_chip *jzgc,
				   u8 offset, int value)
{
	if (jzgc->jzpc->version >= ID_JZ4760)
		ingenic_gpio_set_bit(jzgc, JZ4760_GPIO_PAT0, offset, !!value);
	else
		ingenic_gpio_set_bit(jzgc, JZ4740_GPIO_DATA, offset, !!value);
}