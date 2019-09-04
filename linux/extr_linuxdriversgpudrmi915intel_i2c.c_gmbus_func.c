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
typedef  int u32 ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int (* functionality ) (struct i2c_adapter*) ;} ;

/* Variables and functions */
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_BLOCK_PROC_CALL ; 
 int I2C_FUNC_SMBUS_EMUL ; 
 int I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 TYPE_1__ i2c_bit_algo ; 
 int stub1 (struct i2c_adapter*) ; 

__attribute__((used)) static u32 gmbus_func(struct i2c_adapter *adapter)
{
	return i2c_bit_algo.functionality(adapter) &
		(I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
		/* I2C_FUNC_10BIT_ADDR | */
		I2C_FUNC_SMBUS_READ_BLOCK_DATA |
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL);
}