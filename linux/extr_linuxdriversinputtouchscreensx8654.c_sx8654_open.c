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
struct sx8654 {struct i2c_client* client; } ;
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PENTRG ; 
 int /*<<< orphan*/  I2C_REG_TOUCH0 ; 
 int POWDLY_1_1MS ; 
 int RATE_5000CPS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct sx8654* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int sx8654_open(struct input_dev *dev)
{
	struct sx8654 *sx8654 = input_get_drvdata(dev);
	struct i2c_client *client = sx8654->client;
	int error;

	/* enable pen trigger mode */
	error = i2c_smbus_write_byte_data(client, I2C_REG_TOUCH0,
					  RATE_5000CPS | POWDLY_1_1MS);
	if (error) {
		dev_err(&client->dev, "writing to I2C_REG_TOUCH0 failed");
		return error;
	}

	error = i2c_smbus_write_byte(client, CMD_PENTRG);
	if (error) {
		dev_err(&client->dev, "writing command CMD_PENTRG failed");
		return error;
	}

	enable_irq(client->irq);

	return 0;
}