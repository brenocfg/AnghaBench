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
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int als_wait_for_data_ready(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	int ret;
	int retry = 10;

	do {
		msleep(30);
		ret = i2c_smbus_read_byte_data(client, 0x86);
	} while (!(ret & 0x80) && retry--);

	if (retry < 0) {
		dev_warn(dev, "timeout waiting for data ready\n");
		return -ETIMEDOUT;
	}

	return 0;
}