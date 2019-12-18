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
struct nforce2_smbus {scalar_t__ blockops; } ;
struct i2c_adapter {scalar_t__ algo_data; } ;

/* Variables and functions */
 int I2C_FUNC_SMBUS_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_BYTE ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_PEC ; 
 int I2C_FUNC_SMBUS_QUICK ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 

__attribute__((used)) static u32 nforce2_func(struct i2c_adapter *adapter)
{
	/* other functionality might be possible, but is not tested */
	return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_PEC |
	       (((struct nforce2_smbus *)adapter->algo_data)->blockops ?
		I2C_FUNC_SMBUS_BLOCK_DATA : 0);
}