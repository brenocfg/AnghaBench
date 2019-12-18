#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct regulator_dev {TYPE_1__* desc; } ;
struct max1586_data {unsigned int v6_curr_sel; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int* volt_table; } ;

/* Variables and functions */
 int I2C_V6_SELECT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 struct max1586_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max1586_v6_set_voltage_sel(struct regulator_dev *rdev,
				      unsigned int selector)
{
	struct max1586_data *max1586 = rdev_get_drvdata(rdev);
	struct i2c_client *client = max1586->client;
	u8 v6_prog;
	int ret;

	dev_dbg(&client->dev, "changing voltage v6 to %dmv\n",
		rdev->desc->volt_table[selector] / 1000);

	v6_prog = I2C_V6_SELECT | (u8) selector;
	ret = i2c_smbus_write_byte(client, v6_prog);
	if (ret)
		return ret;

	max1586->v6_curr_sel = selector;

	return 0;
}