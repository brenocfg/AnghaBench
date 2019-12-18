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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (unsigned int,unsigned int) ; 

int ms_sensors_reset(void *cli, u8 cmd, unsigned int delay)
{
	int ret;
	struct i2c_client *client = cli;

	ret = i2c_smbus_write_byte(client, cmd);
	if (ret) {
		dev_err(&client->dev, "Failed to reset device\n");
		return ret;
	}
	usleep_range(delay, delay + 1000);

	return 0;
}