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
struct stm32f7_i2c_dev {scalar_t__* slave; } ;

/* Variables and functions */
 int STM32F7_I2C_MAX_SLAVE ; 

__attribute__((used)) static bool stm32f7_i2c_is_slave_busy(struct stm32f7_i2c_dev *i2c_dev)
{
	int i, busy;

	busy = 0;
	for (i = 0; i < STM32F7_I2C_MAX_SLAVE; i++) {
		if (i2c_dev->slave[i])
			busy++;
	}

	return i == busy;
}