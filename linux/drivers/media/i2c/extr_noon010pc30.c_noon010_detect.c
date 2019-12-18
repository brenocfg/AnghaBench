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
struct noon010_info {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_ID_REG ; 
 int ENODEV ; 
 int NOON010PC30_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_disable (struct noon010_info*) ; 
 int power_enable (struct noon010_info*) ; 

__attribute__((used)) static int noon010_detect(struct i2c_client *client, struct noon010_info *info)
{
	int ret;

	ret = power_enable(info);
	if (ret)
		return ret;

	ret = i2c_smbus_read_byte_data(client, DEVICE_ID_REG);
	if (ret < 0)
		dev_err(&client->dev, "I2C read failed: 0x%X\n", ret);

	power_disable(info);

	return ret == NOON010PC30_ID ? 0 : -ENODEV;
}