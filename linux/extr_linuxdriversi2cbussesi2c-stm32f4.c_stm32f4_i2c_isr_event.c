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
struct stm32f4_i2c_msg {int addr; } ;
struct stm32f4_i2c_dev {scalar_t__ base; int /*<<< orphan*/  dev; struct stm32f4_i2c_msg msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ STM32F4_I2C_CR2 ; 
 int STM32F4_I2C_CR2_IRQ_MASK ; 
 int STM32F4_I2C_CR2_ITBUFEN ; 
 scalar_t__ STM32F4_I2C_SR1 ; 
 int STM32F4_I2C_SR1_ADDR ; 
 int STM32F4_I2C_SR1_BTF ; 
 int STM32F4_I2C_SR1_ITBUFEN_MASK ; 
 int STM32F4_I2C_SR1_ITEVTEN_MASK ; 
 int STM32F4_I2C_SR1_RXNE ; 
 int STM32F4_I2C_SR1_SB ; 
 int STM32F4_I2C_SR1_TXE ; 
 scalar_t__ STM32F4_I2C_SR2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32f4_i2c_handle_read (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f4_i2c_handle_rx_addr (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f4_i2c_handle_rx_done (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f4_i2c_handle_write (struct stm32f4_i2c_dev*) ; 
 int /*<<< orphan*/  stm32f4_i2c_write_byte (struct stm32f4_i2c_dev*,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm32f4_i2c_isr_event(int irq, void *data)
{
	struct stm32f4_i2c_dev *i2c_dev = data;
	struct stm32f4_i2c_msg *msg = &i2c_dev->msg;
	u32 possible_status = STM32F4_I2C_SR1_ITEVTEN_MASK;
	u32 status, ien, event, cr2;

	cr2 = readl_relaxed(i2c_dev->base + STM32F4_I2C_CR2);
	ien = cr2 & STM32F4_I2C_CR2_IRQ_MASK;

	/* Update possible_status if buffer interrupt is enabled */
	if (ien & STM32F4_I2C_CR2_ITBUFEN)
		possible_status |= STM32F4_I2C_SR1_ITBUFEN_MASK;

	status = readl_relaxed(i2c_dev->base + STM32F4_I2C_SR1);
	event = status & possible_status;
	if (!event) {
		dev_dbg(i2c_dev->dev,
			"spurious evt irq (status=0x%08x, ien=0x%08x)\n",
			status, ien);
		return IRQ_NONE;
	}

	/* Start condition generated */
	if (event & STM32F4_I2C_SR1_SB)
		stm32f4_i2c_write_byte(i2c_dev, msg->addr);

	/* I2C Address sent */
	if (event & STM32F4_I2C_SR1_ADDR) {
		if (msg->addr & I2C_M_RD)
			stm32f4_i2c_handle_rx_addr(i2c_dev);
		else
			readl_relaxed(i2c_dev->base + STM32F4_I2C_SR2);

		/*
		 * Enable buffer interrupts for RX not empty and TX empty
		 * events
		 */
		cr2 |= STM32F4_I2C_CR2_ITBUFEN;
		writel_relaxed(cr2, i2c_dev->base + STM32F4_I2C_CR2);
	}

	/* TX empty */
	if ((event & STM32F4_I2C_SR1_TXE) && !(msg->addr & I2C_M_RD))
		stm32f4_i2c_handle_write(i2c_dev);

	/* RX not empty */
	if ((event & STM32F4_I2C_SR1_RXNE) && (msg->addr & I2C_M_RD))
		stm32f4_i2c_handle_read(i2c_dev);

	/*
	 * The BTF (Byte Transfer finished) event occurs when:
	 * - in reception : a new byte is received in the shift register
	 * but the previous byte has not been read yet from data register
	 * - in transmission: a new byte should be sent but the data register
	 * has not been written yet
	 */
	if (event & STM32F4_I2C_SR1_BTF) {
		if (msg->addr & I2C_M_RD)
			stm32f4_i2c_handle_rx_done(i2c_dev);
		else
			stm32f4_i2c_handle_write(i2c_dev);
	}

	return IRQ_HANDLED;
}