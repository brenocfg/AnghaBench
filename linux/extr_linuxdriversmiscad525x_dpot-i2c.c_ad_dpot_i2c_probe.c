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
struct i2c_device_id {int /*<<< orphan*/  name; int /*<<< orphan*/  driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct ad_dpot_bus_data {int /*<<< orphan*/ * bops; struct i2c_client* client; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int ad_dpot_probe (int /*<<< orphan*/ *,struct ad_dpot_bus_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad_dpot_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	struct ad_dpot_bus_data bdata = {
		.client = client,
		.bops = &bops,
	};

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_err(&client->dev, "SMBUS Word Data not Supported\n");
		return -EIO;
	}

	return ad_dpot_probe(&client->dev, &bdata, id->driver_data, id->name);
}