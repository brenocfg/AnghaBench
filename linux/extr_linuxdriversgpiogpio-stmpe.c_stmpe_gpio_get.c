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
typedef  int u8 ;
struct stmpe_gpio {struct stmpe* stmpe; } ;
struct stmpe {int* regs; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int STMPE_IDX_GPMR_LSB ; 
 struct stmpe_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int stmpe_reg_read (struct stmpe*,int) ; 

__attribute__((used)) static int stmpe_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct stmpe_gpio *stmpe_gpio = gpiochip_get_data(chip);
	struct stmpe *stmpe = stmpe_gpio->stmpe;
	u8 reg = stmpe->regs[STMPE_IDX_GPMR_LSB + (offset / 8)];
	u8 mask = BIT(offset % 8);
	int ret;

	ret = stmpe_reg_read(stmpe, reg);
	if (ret < 0)
		return ret;

	return !!(ret & mask);
}