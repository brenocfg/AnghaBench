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
 int /*<<< orphan*/  W83795_REG_DEVICEID ; 
 int /*<<< orphan*/  W83795_REG_DEVICEID_A ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w83795_get_device_id(struct i2c_client *client)
{
	int device_id;

	device_id = i2c_smbus_read_byte_data(client, W83795_REG_DEVICEID);

	/*
	 * Special case for rev. A chips; can't be checked first because later
	 * revisions emulate this for compatibility
	 */
	if (device_id < 0 || (device_id & 0xf0) != 0x50) {
		int alt_id;

		alt_id = i2c_smbus_read_byte_data(client,
						  W83795_REG_DEVICEID_A);
		if (alt_id == 0x50)
			device_id = alt_id;
	}

	return device_id;
}