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

/* Variables and functions */
 unsigned long peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned long) ; 
 int sw_i2c_clk_gpio ; 
 int /*<<< orphan*/  sw_i2c_clk_gpio_data_dir_reg ; 
 int /*<<< orphan*/  sw_i2c_clk_gpio_data_reg ; 

__attribute__((used)) static void sw_i2c_scl(unsigned char value)
{
	unsigned long gpio_data;
	unsigned long gpio_dir;

	gpio_dir = peek32(sw_i2c_clk_gpio_data_dir_reg);
	if (value) {    /* High */
		/*
		 * Set direction as input. This will automatically
		 * pull the signal up.
		 */
		gpio_dir &= ~(1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_dir_reg, gpio_dir);
	} else {        /* Low */
		/* Set the signal down */
		gpio_data = peek32(sw_i2c_clk_gpio_data_reg);
		gpio_data &= ~(1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_reg, gpio_data);

		/* Set direction as output */
		gpio_dir |= (1 << sw_i2c_clk_gpio);
		poke32(sw_i2c_clk_gpio_data_dir_reg, gpio_dir);
	}
}