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
 int /*<<< orphan*/  GPIO_MUX ; 
 unsigned int GPIO_MUX_30 ; 
 unsigned int GPIO_MUX_31 ; 
 int /*<<< orphan*/  I2C_CTRL ; 
 unsigned int I2C_CTRL_EN ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sm750_enable_i2c (int /*<<< orphan*/ ) ; 

void sm750_hw_i2c_close(void)
{
	unsigned int value;

	/* Disable I2C controller */
	value = peek32(I2C_CTRL) & ~I2C_CTRL_EN;
	poke32(I2C_CTRL, value);

	/* Disable I2C Power */
	sm750_enable_i2c(0);

	/* Set GPIO 30 & 31 back as GPIO pins */
	value = peek32(GPIO_MUX);
	value &= ~GPIO_MUX_30;
	value &= ~GPIO_MUX_31;
	poke32(GPIO_MUX, value);
}