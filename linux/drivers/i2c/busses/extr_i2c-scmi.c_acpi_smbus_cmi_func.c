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
struct i2c_adapter {struct acpi_smbus_cmi* algo_data; } ;
struct acpi_smbus_cmi {int cap_read; int cap_write; } ;

/* Variables and functions */
 int I2C_FUNC_SMBUS_QUICK ; 
 int I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_READ_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_READ_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BLOCK_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_WORD_DATA ; 

__attribute__((used)) static u32 acpi_smbus_cmi_func(struct i2c_adapter *adapter)
{
	struct acpi_smbus_cmi *smbus_cmi = adapter->algo_data;
	u32 ret;

	ret = smbus_cmi->cap_read | smbus_cmi->cap_write ?
		I2C_FUNC_SMBUS_QUICK : 0;

	ret |= smbus_cmi->cap_read ?
		(I2C_FUNC_SMBUS_READ_BYTE |
		I2C_FUNC_SMBUS_READ_BYTE_DATA |
		I2C_FUNC_SMBUS_READ_WORD_DATA |
		I2C_FUNC_SMBUS_READ_BLOCK_DATA) : 0;

	ret |= smbus_cmi->cap_write ?
		(I2C_FUNC_SMBUS_WRITE_BYTE |
		I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
		I2C_FUNC_SMBUS_WRITE_WORD_DATA |
		I2C_FUNC_SMBUS_WRITE_BLOCK_DATA) : 0;

	return ret;
}