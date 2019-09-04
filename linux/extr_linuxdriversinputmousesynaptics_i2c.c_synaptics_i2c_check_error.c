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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int CONFIGURED_MSK ; 
 int /*<<< orphan*/  DEVICE_STATUS_REG ; 
 int ERROR_MSK ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int synaptics_i2c_reset_config (struct i2c_client*) ; 

__attribute__((used)) static int synaptics_i2c_check_error(struct i2c_client *client)
{
	int status, ret = 0;

	status = i2c_smbus_read_byte_data(client, DEVICE_STATUS_REG) &
		(CONFIGURED_MSK | ERROR_MSK);

	if (status != CONFIGURED_MSK)
		ret = synaptics_i2c_reset_config(client);

	return ret;
}