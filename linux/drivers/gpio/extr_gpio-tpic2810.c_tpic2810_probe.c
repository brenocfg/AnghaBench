#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct tpic2810 {TYPE_1__ chip; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tpic2810* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int gpiochip_add_data (TYPE_1__*,struct tpic2810*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tpic2810*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ template_chip ; 

__attribute__((used)) static int tpic2810_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct tpic2810 *gpio;
	int ret;

	gpio = devm_kzalloc(&client->dev, sizeof(*gpio), GFP_KERNEL);
	if (!gpio)
		return -ENOMEM;

	i2c_set_clientdata(client, gpio);

	gpio->chip = template_chip;
	gpio->chip.parent = &client->dev;

	gpio->client = client;

	mutex_init(&gpio->lock);

	ret = gpiochip_add_data(&gpio->chip, gpio);
	if (ret < 0) {
		dev_err(&client->dev, "Unable to register gpiochip\n");
		return ret;
	}

	return 0;
}