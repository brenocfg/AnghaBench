#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct stm32f7_i2c_timings {int /*<<< orphan*/  scll; int /*<<< orphan*/  sclh; int /*<<< orphan*/  sdadel; int /*<<< orphan*/  scldel; int /*<<< orphan*/  presc; } ;
struct TYPE_2__ {scalar_t__ analog_filter; } ;
struct stm32f7_i2c_dev {scalar_t__ base; TYPE_1__ setup; struct stm32f7_i2c_timings timing; } ;

/* Variables and functions */
 scalar_t__ STM32F7_I2C_CR1 ; 
 int /*<<< orphan*/  STM32F7_I2C_CR1_ANFOFF ; 
 int /*<<< orphan*/  STM32F7_I2C_CR1_PE ; 
 scalar_t__ STM32F7_I2C_TIMINGR ; 
 int /*<<< orphan*/  STM32F7_I2C_TIMINGR_PRESC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32F7_I2C_TIMINGR_SCLDEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32F7_I2C_TIMINGR_SCLH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32F7_I2C_TIMINGR_SCLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32F7_I2C_TIMINGR_SDADEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32f7_i2c_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32f7_i2c_set_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32f7_i2c_hw_config(struct stm32f7_i2c_dev *i2c_dev)
{
	struct stm32f7_i2c_timings *t = &i2c_dev->timing;
	u32 timing = 0;

	/* Timing settings */
	timing |= STM32F7_I2C_TIMINGR_PRESC(t->presc);
	timing |= STM32F7_I2C_TIMINGR_SCLDEL(t->scldel);
	timing |= STM32F7_I2C_TIMINGR_SDADEL(t->sdadel);
	timing |= STM32F7_I2C_TIMINGR_SCLH(t->sclh);
	timing |= STM32F7_I2C_TIMINGR_SCLL(t->scll);
	writel_relaxed(timing, i2c_dev->base + STM32F7_I2C_TIMINGR);

	/* Enable I2C */
	if (i2c_dev->setup.analog_filter)
		stm32f7_i2c_clr_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_ANFOFF);
	else
		stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
				     STM32F7_I2C_CR1_ANFOFF);
	stm32f7_i2c_set_bits(i2c_dev->base + STM32F7_I2C_CR1,
			     STM32F7_I2C_CR1_PE);
}