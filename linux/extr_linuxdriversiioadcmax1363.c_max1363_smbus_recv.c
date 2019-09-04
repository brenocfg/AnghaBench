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
 int i2c_smbus_read_byte (struct i2c_client const*) ; 

__attribute__((used)) static int max1363_smbus_recv(const struct i2c_client *client, char *buf,
		int count)
{
	int i, ret;

	for (i = 0; i < count; ++i) {
		ret = i2c_smbus_read_byte(client);
		if (ret < 0)
			return ret;
		buf[i] = ret;
	}

	return count;
}