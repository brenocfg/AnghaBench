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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned short cpu_to_be16 (unsigned short const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int ad5398_write_reg(struct i2c_client *client, const unsigned short data)
{
	unsigned short val;
	int ret;

	val = cpu_to_be16(data);
	ret = i2c_master_send(client, (char *)&val, 2);
	if (ret != 2) {
		dev_err(&client->dev, "I2C write error\n");
		return ret < 0 ? ret : -EIO;
	}

	return 0;
}