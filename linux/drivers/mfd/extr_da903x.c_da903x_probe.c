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
struct i2c_device_id {size_t driver_data; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct da903x_platform_data {int dummy; } ;
struct da903x_chip {int events_mask; TYPE_1__* ops; int /*<<< orphan*/  notifier_list; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; struct i2c_client* client; } ;
struct TYPE_2__ {int (* init_chip ) (struct da903x_chip*) ;int /*<<< orphan*/  (* read_events ) (struct da903x_chip*,unsigned int*) ;int /*<<< orphan*/  (* mask_events ) (struct da903x_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int da903x_add_subdevs (struct da903x_chip*,struct da903x_platform_data*) ; 
 int /*<<< orphan*/  da903x_irq_handler ; 
 int /*<<< orphan*/  da903x_irq_work ; 
 TYPE_1__* da903x_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct da903x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct da903x_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct da903x_chip*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da903x_chip*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct da903x_chip*) ; 
 int /*<<< orphan*/  stub2 (struct da903x_chip*,int) ; 
 int /*<<< orphan*/  stub3 (struct da903x_chip*,unsigned int*) ; 

__attribute__((used)) static int da903x_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct da903x_platform_data *pdata = dev_get_platdata(&client->dev);
	struct da903x_chip *chip;
	unsigned int tmp;
	int ret;

	chip = devm_kzalloc(&client->dev, sizeof(struct da903x_chip),
				GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	chip->client = client;
	chip->dev = &client->dev;
	chip->ops = &da903x_ops[id->driver_data];

	mutex_init(&chip->lock);
	INIT_WORK(&chip->irq_work, da903x_irq_work);
	BLOCKING_INIT_NOTIFIER_HEAD(&chip->notifier_list);

	i2c_set_clientdata(client, chip);

	ret = chip->ops->init_chip(chip);
	if (ret)
		return ret;

	/* mask and clear all IRQs */
	chip->events_mask = 0xffffffff;
	chip->ops->mask_events(chip, chip->events_mask);
	chip->ops->read_events(chip, &tmp);

	ret = devm_request_irq(&client->dev, client->irq, da903x_irq_handler,
			IRQF_TRIGGER_FALLING,
			"da903x", chip);
	if (ret) {
		dev_err(&client->dev, "failed to request irq %d\n",
				client->irq);
		return ret;
	}

	return da903x_add_subdevs(chip, pdata);
}