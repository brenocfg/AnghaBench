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
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int component_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tda998x_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda998x_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda998x_ops ; 

__attribute__((used)) static int
tda998x_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_warn(&client->dev, "adapter does not support I2C\n");
		return -EIO;
	}

	ret = tda998x_create(&client->dev);
	if (ret)
		return ret;

	ret = component_add(&client->dev, &tda998x_ops);
	if (ret)
		tda998x_destroy(&client->dev);
	return ret;
}