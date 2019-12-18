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
struct stmpe_gpio {struct stmpe* stmpe; } ;
struct stmpe {int /*<<< orphan*/ * regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int STMPE_IDX_GPDR_LSB ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  stmpe_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_gpio_direction_output(struct gpio_chip *chip,
					 unsigned offset, int val)
{
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(chip);
	struct stmpe *stmpe = stmpe_gpio->stmpe;
	u8 reg = stmpe->regs[STMPE_IDX_GPDR_LSB + (offset / 8)];
	u8 mask = BIT(offset % 8);

	stmpe_gpio_set(chip, offset, val);

	return stmpe_set_bits(stmpe, reg, mask, mask);
}