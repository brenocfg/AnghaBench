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
struct ingenic_gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_PIN ; 
 unsigned int ingenic_gpio_read_reg (struct ingenic_gpio_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ingenic_gpio_get_value(struct ingenic_gpio_chip *jzgc,
					  u8 offset)
{
	unsigned int val = ingenic_gpio_read_reg(jzgc, GPIO_PIN);

	return !!(val & BIT(offset));
}