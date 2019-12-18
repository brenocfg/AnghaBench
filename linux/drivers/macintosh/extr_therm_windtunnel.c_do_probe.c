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
struct i2c_device_id {int driver_data; } ;
struct i2c_client {struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
#define  adm1030 129 
 int attach_fan (struct i2c_client*) ; 
 int attach_thermostat (struct i2c_client*) ; 
#define  ds1775 128 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 

__attribute__((used)) static int
do_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = cl->adapter;

	if( !i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE) )
		return 0;

	switch (id->driver_data) {
	case adm1030:
		return attach_fan( cl );
	case ds1775:
		return attach_thermostat(cl);
	}
	return 0;
}