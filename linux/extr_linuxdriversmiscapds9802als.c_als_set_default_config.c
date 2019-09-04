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
 int /*<<< orphan*/  als_wait_for_data_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 

__attribute__((used)) static int als_set_default_config(struct i2c_client *client)
{
	int ret_val;
	/* Write the command and then switch on */
	ret_val = i2c_smbus_write_byte_data(client, 0x80, 0x01);
	if (ret_val < 0) {
		dev_err(&client->dev, "failed default switch on write\n");
		return ret_val;
	}
	/* detection range: 1~64K Lux, maunal measurement */
	ret_val = i2c_smbus_write_byte_data(client, 0x81, 0x08);
	if (ret_val < 0)
		dev_err(&client->dev, "failed default LUX on write\n");

	/*  We always get 0 for the 1st measurement after system power on,
	 *  so make sure it is finished before user asks for data.
	 */
	als_wait_for_data_ready(&client->dev);

	return ret_val;
}