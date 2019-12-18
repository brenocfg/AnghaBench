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
typedef  int uint32_t ;
typedef  int u32 ;
struct i2c_adapter {TYPE_1__* algo; } ;
struct TYPE_2__ {scalar_t__ reg_slave; } ;

/* Variables and functions */
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SLAVE ; 
 int I2C_FUNC_SMBUS_EMUL ; 
 int I2C_FUNC_SMBUS_QUICK ; 

__attribute__((used)) static uint32_t bcm_iproc_i2c_functionality(struct i2c_adapter *adap)
{
	u32 val;

	/* We do not support the SMBUS Quick command */
	val = I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);

	if (adap->algo->reg_slave)
		val |= I2C_FUNC_SLAVE;

	return val;
}