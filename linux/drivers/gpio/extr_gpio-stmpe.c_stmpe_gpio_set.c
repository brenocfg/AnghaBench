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
 size_t STMPE_IDX_GPCR_LSB ; 
 size_t STMPE_IDX_GPSR_LSB ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  stmpe_reg_write (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmpe_gpio_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(chip);
	struct stmpe *stmpe = stmpe_gpio->stmpe;
	int which = val ? STMPE_IDX_GPSR_LSB : STMPE_IDX_GPCR_LSB;
	u8 reg = stmpe->regs[which + (offset / 8)];
	u8 mask = BIT(offset % 8);

	/*
	 * Some variants have single register for gpio set/clear functionality.
	 * For them we need to write 0 to clear and 1 to set.
	 */
	if (stmpe->regs[STMPE_IDX_GPSR_LSB] == stmpe->regs[STMPE_IDX_GPCR_LSB])
		stmpe_set_bits(stmpe, reg, mask, val ? mask : 0);
	else
		stmpe_reg_write(stmpe, reg, mask);
}