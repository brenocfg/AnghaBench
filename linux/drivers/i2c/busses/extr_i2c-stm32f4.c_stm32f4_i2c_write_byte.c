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
struct stm32f4_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ STM32F4_I2C_DR ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32f4_i2c_write_byte(struct stm32f4_i2c_dev *i2c_dev, u8 byte)
{
	writel_relaxed(byte, i2c_dev->base + STM32F4_I2C_DR);
}