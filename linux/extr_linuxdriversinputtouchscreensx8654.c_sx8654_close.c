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
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MANUAL ; 
 int /*<<< orphan*/  I2C_REG_TOUCH0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sx8654* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void sx8654_close(struct input_dev *dev)
{
	struct sx8654 *sx8654 = input_get_drvdata(dev);
	struct i2c_client *client = sx8654->client;
	int error;

	disable_irq(client->irq);

	/* enable manual mode mode */
	error = i2c_smbus_write_byte(client, CMD_MANUAL);
	if (error) {
		dev_err(&client->dev, "writing command CMD_MANUAL failed");
		return;
	}

	error = i2c_smbus_write_byte_data(client, I2C_REG_TOUCH0, 0);
	if (error) {
		dev_err(&client->dev, "writing to I2C_REG_TOUCH0 failed");
		return;
	}
}