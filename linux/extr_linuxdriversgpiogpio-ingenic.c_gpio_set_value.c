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
 int /*<<< orphan*/  JZ4740_GPIO_DATA ; 
 int /*<<< orphan*/  JZ4770_GPIO_PAT0 ; 
 int /*<<< orphan*/  gpio_ingenic_set_bit (struct ingenic_gpio_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpio_set_value(struct ingenic_gpio_chip *jzgc, u8 offset, int value)
{
	if (jzgc->version >= ID_JZ4770)
		gpio_ingenic_set_bit(jzgc, JZ4770_GPIO_PAT0, offset, !!value);
	else
		gpio_ingenic_set_bit(jzgc, JZ4740_GPIO_DATA, offset, !!value);
}