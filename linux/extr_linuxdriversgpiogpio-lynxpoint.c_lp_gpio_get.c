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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int IN_LVL_BIT ; 
 int /*<<< orphan*/  LP_CONFIG1 ; 
 int inl (unsigned long) ; 
 unsigned long lp_gpio_reg (struct gpio_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	unsigned long reg = lp_gpio_reg(chip, offset, LP_CONFIG1);
	return !!(inl(reg) & IN_LVL_BIT);
}