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
struct iqs5xx_private {scalar_t__ input; int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_gpio; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_device_add_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iqs5xx_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iqs5xx_private*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iqs5xx_private*) ; 
 int input_register_device (scalar_t__) ; 
 int /*<<< orphan*/  iqs5xx_attr_group ; 
 int iqs5xx_dev_init (struct i2c_client*) ; 
 int /*<<< orphan*/  iqs5xx_irq ; 
 int /*<<< orphan*/  iqs5xx_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int iqs5xx_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct iqs5xx_private *iqs5xx;
	int error;

	iqs5xx = devm_kzalloc(&client->dev, sizeof(*iqs5xx), GFP_KERNEL);
	if (!iqs5xx)
		return -ENOMEM;

	i2c_set_clientdata(client, iqs5xx);
	iqs5xx->client = client;

	iqs5xx->reset_gpio = devm_gpiod_get(&client->dev,
					    "reset", GPIOD_OUT_LOW);
	if (IS_ERR(iqs5xx->reset_gpio)) {
		error = PTR_ERR(iqs5xx->reset_gpio);
		dev_err(&client->dev, "Failed to request GPIO: %d\n", error);
		return error;
	}

	mutex_init(&iqs5xx->lock);

	iqs5xx_reset(client);
	usleep_range(10000, 10100);

	error = iqs5xx_dev_init(client);
	if (error)
		return error;

	error = devm_request_threaded_irq(&client->dev, client->irq,
					  NULL, iqs5xx_irq, IRQF_ONESHOT,
					  client->name, iqs5xx);
	if (error) {
		dev_err(&client->dev, "Failed to request IRQ: %d\n", error);
		return error;
	}

	error = devm_device_add_group(&client->dev, &iqs5xx_attr_group);
	if (error) {
		dev_err(&client->dev, "Failed to add attributes: %d\n", error);
		return error;
	}

	if (iqs5xx->input) {
		error = input_register_device(iqs5xx->input);
		if (error)
			dev_err(&client->dev,
				"Failed to register device: %d\n",
				error);
	}

	return error;
}