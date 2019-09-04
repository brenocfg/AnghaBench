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
typedef  int u32 ;
struct stm32f4_i2c_dev {scalar_t__ speed; scalar_t__ base; int /*<<< orphan*/  parent_rate; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZ_TO_MHZ ; 
 scalar_t__ STM32F4_I2C_TRISE ; 
 int /*<<< orphan*/  STM32F4_I2C_TRISE_VALUE (int) ; 
 scalar_t__ STM32_I2C_SPEED_STANDARD ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32f4_i2c_set_rise_time(struct stm32f4_i2c_dev *i2c_dev)
{
	u32 freq = DIV_ROUND_UP(i2c_dev->parent_rate, HZ_TO_MHZ);
	u32 trise;

	/*
	 * These bits must be programmed with the maximum SCL rise time given in
	 * the I2C bus specification, incremented by 1.
	 *
	 * In standard mode, the maximum allowed SCL rise time is 1000 ns.
	 * If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to
	 * 0x08 so period = 125 ns therefore the TRISE[5:0] bits must be
	 * programmed with 0x9. (1000 ns / 125 ns + 1)
	 * So, for I2C standard mode TRISE = FREQ[5:0] + 1
	 *
	 * In fast mode, the maximum allowed SCL rise time is 300 ns.
	 * If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to
	 * 0x08 so period = 125 ns therefore the TRISE[5:0] bits must be
	 * programmed with 0x3. (300 ns / 125 ns + 1)
	 * So, for I2C fast mode TRISE = FREQ[5:0] * 300 / 1000 + 1
	 *
	 * Function stm32f4_i2c_set_periph_clk_freq made sure that parent rate
	 * is not higher than 46 MHz . As a result trise is at most 4 bits wide
	 * and so fits into the TRISE bits [5:0].
	 */
	if (i2c_dev->speed == STM32_I2C_SPEED_STANDARD)
		trise = freq + 1;
	else
		trise = freq * 3 / 10 + 1;

	writel_relaxed(STM32F4_I2C_TRISE_VALUE(trise),
		       i2c_dev->base + STM32F4_I2C_TRISE);
}