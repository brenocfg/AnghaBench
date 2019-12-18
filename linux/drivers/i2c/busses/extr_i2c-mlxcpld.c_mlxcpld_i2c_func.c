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
struct mlxcpld_i2c_priv {scalar_t__ smbus_block; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_EMUL ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 struct mlxcpld_i2c_priv* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static u32 mlxcpld_i2c_func(struct i2c_adapter *adap)
{
	struct mlxcpld_i2c_priv *priv = i2c_get_adapdata(adap);

	if (priv->smbus_block)
		return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
			I2C_FUNC_SMBUS_I2C_BLOCK | I2C_FUNC_SMBUS_BLOCK_DATA;
	else
		return I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL |
			I2C_FUNC_SMBUS_I2C_BLOCK;
}