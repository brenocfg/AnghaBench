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
struct stm32f7_i2c_dev {scalar_t__ base; int /*<<< orphan*/  dev; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ STM32F7_I2C_CR1 ; 
 int /*<<< orphan*/  STM32F7_I2C_CR1_PE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 struct stm32f7_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  stm32f7_i2c_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32f7_i2c_hw_config (struct stm32f7_i2c_dev*) ; 

__attribute__((used)) static int stm32f7_i2c_release_bus(struct i2c_adapter *i2c_adap)
{
	struct stm32f7_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);

	dev_info(i2c_dev->dev, "Trying to recover bus\n");

	stm32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_PE);

	stm32f7_i2c_hw_config(i2c_dev);

	return 0;
}