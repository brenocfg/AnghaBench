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
struct stm32f4_i2c_dev {scalar_t__ speed; int parent_rate; scalar_t__ base; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 scalar_t__ STM32F4_I2C_CCR ; 
 int STM32F4_I2C_CCR_CCR (int) ; 
 int STM32F4_I2C_CCR_FS ; 
 scalar_t__ STM32_I2C_SPEED_STANDARD ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32f4_i2c_set_speed_mode(struct stm32f4_i2c_dev *i2c_dev)
{
	u32 val;
	u32 ccr = 0;

	if (i2c_dev->speed == STM32_I2C_SPEED_STANDARD) {
		/*
		 * In standard mode:
		 * t_scl_high = t_scl_low = CCR * I2C parent clk period
		 * So to reach 100 kHz, we have:
		 * CCR = I2C parent rate / 100 kHz >> 1
		 *
		 * For example with parent rate = 2 MHz:
		 * CCR = 2000000 / (100000 << 1) = 10
		 * t_scl_high = t_scl_low = 10 * (1 / 2000000) = 5000 ns
		 * t_scl_high + t_scl_low = 10000 ns so 100 kHz is reached
		 *
		 * Function stm32f4_i2c_set_periph_clk_freq made sure that
		 * parent rate is not higher than 46 MHz . As a result val
		 * is at most 8 bits wide and so fits into the CCR bits [11:0].
		 */
		val = i2c_dev->parent_rate / (100000 << 1);
	} else {
		/*
		 * In fast mode, we compute CCR with duty = 0 as with low
		 * frequencies we are not able to reach 400 kHz.
		 * In that case:
		 * t_scl_high = CCR * I2C parent clk period
		 * t_scl_low = 2 * CCR * I2C parent clk period
		 * So, CCR = I2C parent rate / (400 kHz * 3)
		 *
		 * For example with parent rate = 6 MHz:
		 * CCR = 6000000 / (400000 * 3) = 5
		 * t_scl_high = 5 * (1 / 6000000) = 833 ns > 600 ns
		 * t_scl_low = 2 * 5 * (1 / 6000000) = 1667 ns > 1300 ns
		 * t_scl_high + t_scl_low = 2500 ns so 400 kHz is reached
		 *
		 * Function stm32f4_i2c_set_periph_clk_freq made sure that
		 * parent rate is not higher than 46 MHz . As a result val
		 * is at most 6 bits wide and so fits into the CCR bits [11:0].
		 */
		val = DIV_ROUND_UP(i2c_dev->parent_rate, 400000 * 3);

		/* Select Fast mode */
		ccr |= STM32F4_I2C_CCR_FS;
	}

	ccr |= STM32F4_I2C_CCR_CCR(val);
	writel_relaxed(ccr, i2c_dev->base + STM32F4_I2C_CCR);
}