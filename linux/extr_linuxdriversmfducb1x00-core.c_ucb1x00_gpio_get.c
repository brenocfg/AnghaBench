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
struct ucb1x00 {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IO_DATA ; 
 struct ucb1x00* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ucb1x00_disable (struct ucb1x00*) ; 
 int /*<<< orphan*/  ucb1x00_enable (struct ucb1x00*) ; 
 unsigned int ucb1x00_reg_read (struct ucb1x00*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucb1x00_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct ucb1x00 *ucb = gpiochip_get_data(chip);
	unsigned val;

	ucb1x00_enable(ucb);
	val = ucb1x00_reg_read(ucb, UCB_IO_DATA);
	ucb1x00_disable(ucb);

	return !!(val & (1 << offset));
}