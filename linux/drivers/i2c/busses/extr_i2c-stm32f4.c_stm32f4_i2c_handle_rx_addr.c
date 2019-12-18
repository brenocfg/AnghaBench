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
struct stm32f4_i2c_msg {int count; int /*<<< orphan*/  stop; } ;
struct stm32f4_i2c_dev {scalar_t__ base; struct stm32f4_i2c_msg msg; } ;

/* Variables and functions */
 scalar_t__ STM32F4_I2C_CR1 ; 
 int STM32F4_I2C_CR1_ACK ; 
 int STM32F4_I2C_CR1_POS ; 
 int STM32F4_I2C_CR1_START ; 
 int STM32F4_I2C_CR1_STOP ; 
 scalar_t__ STM32F4_I2C_SR2 ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32f4_i2c_terminate_xfer (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32f4_i2c_handle_rx_addr(struct stm32f4_i2c_dev *i2c_dev)
{
	struct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 cr1;

	switch (msg->count) {
	case 0:
		stm32f4_i2c_terminate_xfer(i2c_dev);

		/* Clear ADDR flag */
		readl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		break;
	case 1:
		/*
		 * Single byte reception:
		 * Enable NACK and reset POS (Acknowledge position).
		 * Then, clear ADDR flag and set STOP or RepSTART.
		 * In that way, the NACK and STOP or RepStart pulses will be
		 * sent as soon as the byte will be received in shift register
		 */
		cr1 = readl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 &= ~(STM32F4_I2C_CR1_ACK | STM32F4_I2C_CR1_POS);
		writel_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		readl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);

		if (msg->stop)
			cr1 |= STM32F4_I2C_CR1_STOP;
		else
			cr1 |= STM32F4_I2C_CR1_START;
		writel_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);
		break;
	case 2:
		/*
		 * 2-byte reception:
		 * Enable NACK, set POS (NACK position) and clear ADDR flag.
		 * In that way, NACK will be sent for the next byte which will
		 * be received in the shift register instead of the current
		 * one.
		 */
		cr1 = readl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 &= ~STM32F4_I2C_CR1_ACK;
		cr1 |= STM32F4_I2C_CR1_POS;
		writel_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		readl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		break;

	default:
		/*
		 * N-byte reception:
		 * Enable ACK, reset POS (ACK postion) and clear ADDR flag.
		 * In that way, ACK will be sent as soon as the current byte
		 * will be received in the shift register
		 */
		cr1 = readl_relaxed(i2c_dev->base + STM32F4_I2C_CR1);
		cr1 |= STM32F4_I2C_CR1_ACK;
		cr1 &= ~STM32F4_I2C_CR1_POS;
		writel_relaxed(cr1, i2c_dev->base + STM32F4_I2C_CR1);

		readl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);
		break;
	}
}