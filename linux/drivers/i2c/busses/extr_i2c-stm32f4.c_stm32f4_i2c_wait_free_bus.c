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
struct stm32f4_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ STM32F4_I2C_SR2 ; 
 int STM32F4_I2C_SR2_BUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int readl_relaxed_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int stm32f4_i2c_wait_free_bus(struct stm32f4_i2c_dev *i2c_dev)
{
	u32 status;
	int ret;

	ret = readl_relaxed_poll_timeout(i2c_dev->base + STM32F4_I2C_SR2,
					 status,
					 !(status & STM32F4_I2C_SR2_BUSY),
					 10, 1000);
	if (ret) {
		dev_dbg(i2c_dev->dev, "bus not free\n");
		ret = -EBUSY;
	}

	return ret;
}