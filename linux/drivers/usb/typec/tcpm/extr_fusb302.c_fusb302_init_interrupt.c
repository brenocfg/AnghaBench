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
struct fusb302_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB_REG_CONTROL0 ; 
 int /*<<< orphan*/  FUSB_REG_CONTROL0_INT_MASK ; 
 int /*<<< orphan*/  FUSB_REG_MASK ; 
 int /*<<< orphan*/  FUSB_REG_MASKA ; 
 int /*<<< orphan*/  FUSB_REG_MASKB ; 
 int FUSB_REG_MASK_VBUSOK ; 
 int fusb302_i2c_clear_bits (struct fusb302_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fusb302_i2c_write (struct fusb302_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fusb302_init_interrupt(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_MASK,
				0xFF & ~FUSB_REG_MASK_VBUSOK);
	if (ret < 0)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKA, 0xFF);
	if (ret < 0)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKB, 0xFF);
	if (ret < 0)
		return ret;
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL0,
				     FUSB_REG_CONTROL0_INT_MASK);
	if (ret < 0)
		return ret;

	return ret;
}