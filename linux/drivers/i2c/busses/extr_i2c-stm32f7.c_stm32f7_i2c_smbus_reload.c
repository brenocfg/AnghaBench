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
typedef  int u32 ;
struct stm32f7_i2c_msg {int /*<<< orphan*/  count; int /*<<< orphan*/ * buf; } ;
struct stm32f7_i2c_dev {scalar_t__ base; struct stm32f7_i2c_msg f7_msg; } ;

/* Variables and functions */
 scalar_t__ STM32F7_I2C_CR2 ; 
 int STM32F7_I2C_CR2_NBYTES (int /*<<< orphan*/ ) ; 
 int STM32F7_I2C_CR2_NBYTES_MASK ; 
 int STM32F7_I2C_CR2_RELOAD ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stm32f7_i2c_read_rx_data (struct stm32f7_i2c_dev*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32f7_i2c_smbus_reload(struct stm32f7_i2c_dev *i2c_dev)
{
	struct stm32f7_i2c_msg *f7_msg = &i2c_dev->f7_msg;
	u32 cr2;
	u8 *val;

	/*
	 * For I2C_SMBUS_BLOCK_DATA && I2C_SMBUS_BLOCK_PROC_CALL, the first
	 * data received inform us how many data will follow.
	 */
	stm32f7_i2c_read_rx_data(i2c_dev);

	/*
	 * Update NBYTES with the value read to continue the transfer
	 */
	val = f7_msg->buf - sizeof(u8);
	f7_msg->count = *val;
	cr2 = readl_relaxed(i2c_dev->base + STM32F7_I2C_CR2);
	cr2 &= ~(STM32F7_I2C_CR2_NBYTES_MASK | STM32F7_I2C_CR2_RELOAD);
	cr2 |= STM32F7_I2C_CR2_NBYTES(f7_msg->count);
	writel_relaxed(cr2, i2c_dev->base + STM32F7_I2C_CR2);
}