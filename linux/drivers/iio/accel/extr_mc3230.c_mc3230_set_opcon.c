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
struct mc3230_data {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MC3230_MODE_OPCON_MASK ; 
 int /*<<< orphan*/  MC3230_REG_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mc3230_set_opcon(struct mc3230_data *data, int opcon)
{
	int ret;
	struct i2c_client *client = data->client;

	ret = i2c_smbus_read_byte_data(client, MC3230_REG_MODE);
	if (ret < 0) {
		dev_err(&client->dev, "failed to read mode reg: %d\n", ret);
		return ret;
	}

	ret &= ~MC3230_MODE_OPCON_MASK;
	ret |= opcon;

	ret = i2c_smbus_write_byte_data(client, MC3230_REG_MODE, ret);
	if (ret < 0) {
		dev_err(&client->dev, "failed to write mode reg: %d\n", ret);
		return ret;
	}

	return 0;
}