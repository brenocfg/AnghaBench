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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_AQ_NO_ZERO_LEN ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_EMUL ; 
 int I2C_FUNC_SMBUS_QUICK ; 
 scalar_t__ i2c_check_quirks (struct i2c_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mtk_i2c_functionality(struct i2c_adapter *adap)
{
	if (i2c_check_quirks(adap, I2C_AQ_NO_ZERO_LEN))
		return I2C_FUNC_I2C |
			(I2C_FUNC_SMBUS_EMUL & ~I2C_FUNC_SMBUS_QUICK);
	else
		return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
}