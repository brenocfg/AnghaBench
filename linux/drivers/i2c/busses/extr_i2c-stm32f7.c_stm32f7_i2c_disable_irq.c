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
typedef  int /*<<< orphan*/  u32 ;
struct stm32f7_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ STM32F7_I2C_CR1 ; 
 int /*<<< orphan*/  stm32f7_i2c_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32f7_i2c_disable_irq(struct stm32f7_i2c_dev *i2c_dev, u32 mask)
{
	stm32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1, mask);
}