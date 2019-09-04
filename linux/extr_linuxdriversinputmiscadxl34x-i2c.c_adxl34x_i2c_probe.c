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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct adxl34x {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 scalar_t__ IS_ERR (struct adxl34x*) ; 
 int PTR_ERR (struct adxl34x*) ; 
 int /*<<< orphan*/  adxl34x_i2c_bops ; 
 struct adxl34x* adxl34x_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adxl34x_smbus_bops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adxl34x*) ; 

__attribute__((used)) static int adxl34x_i2c_probe(struct i2c_client *client,
				       const struct i2c_device_id *id)
{
	struct adxl34x *ac;
	int error;

	error = i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA);
	if (!error) {
		dev_err(&client->dev, "SMBUS Byte Data not Supported\n");
		return -EIO;
	}

	ac = adxl34x_probe(&client->dev, client->irq, false,
			   i2c_check_functionality(client->adapter,
						   I2C_FUNC_SMBUS_READ_I2C_BLOCK) ?
				&adxl34x_smbus_bops : &adxl34x_i2c_bops);
	if (IS_ERR(ac))
		return PTR_ERR(ac);

	i2c_set_clientdata(client, ac);

	return 0;
}