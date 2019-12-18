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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EIO ; 
 int adv_smbus_read_byte_data_check (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,...) ; 

__attribute__((used)) static s32 adv_smbus_read_byte_data(struct i2c_client *client, u8 command)
{
	int i;

	for (i = 0; i < 3; i++) {
		int ret = adv_smbus_read_byte_data_check(client, command, true);

		if (ret >= 0) {
			if (i)
				v4l_err(client, "read ok after %d retries\n", i);
			return ret;
		}
	}
	v4l_err(client, "read failed\n");
	return -EIO;
}