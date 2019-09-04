#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct aat2870_platform_data {int en_pin; int num_subdevs; TYPE_1__* subdevs; int /*<<< orphan*/  uninit; int /*<<< orphan*/  (* init ) (struct aat2870_data*) ;} ;
struct aat2870_data {int en_pin; int /*<<< orphan*/ * dev; int /*<<< orphan*/  (* init ) (struct aat2870_data*) ;int /*<<< orphan*/  io_lock; int /*<<< orphan*/  update; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  uninit; int /*<<< orphan*/  reg_cache; struct i2c_client* client; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  platform_data; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ id; int /*<<< orphan*/  platform_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_HIGH ; 
 TYPE_2__* aat2870_devs ; 
 int /*<<< orphan*/  aat2870_disable (struct aat2870_data*) ; 
 int /*<<< orphan*/  aat2870_enable (struct aat2870_data*) ; 
 int /*<<< orphan*/  aat2870_init_debugfs (struct aat2870_data*) ; 
 int /*<<< orphan*/  aat2870_read ; 
 int /*<<< orphan*/  aat2870_regs ; 
 int /*<<< orphan*/  aat2870_update ; 
 int /*<<< orphan*/  aat2870_write ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct aat2870_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct aat2870_data*) ; 
 int devm_gpio_request_one (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 struct aat2870_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct aat2870_data*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aat2870_data*) ; 

__attribute__((used)) static int aat2870_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct aat2870_platform_data *pdata = dev_get_platdata(&client->dev);
	struct aat2870_data *aat2870;
	int i, j;
	int ret = 0;

	aat2870 = devm_kzalloc(&client->dev, sizeof(struct aat2870_data),
				GFP_KERNEL);
	if (!aat2870)
		return -ENOMEM;

	aat2870->dev = &client->dev;
	dev_set_drvdata(aat2870->dev, aat2870);

	aat2870->client = client;
	i2c_set_clientdata(client, aat2870);

	aat2870->reg_cache = aat2870_regs;

	if (pdata->en_pin < 0)
		aat2870->en_pin = -1;
	else
		aat2870->en_pin = pdata->en_pin;

	aat2870->init = pdata->init;
	aat2870->uninit = pdata->uninit;
	aat2870->read = aat2870_read;
	aat2870->write = aat2870_write;
	aat2870->update = aat2870_update;

	mutex_init(&aat2870->io_lock);

	if (aat2870->init)
		aat2870->init(aat2870);

	if (aat2870->en_pin >= 0) {
		ret = devm_gpio_request_one(&client->dev, aat2870->en_pin,
					GPIOF_OUT_INIT_HIGH, "aat2870-en");
		if (ret < 0) {
			dev_err(&client->dev,
				"Failed to request GPIO %d\n", aat2870->en_pin);
			return ret;
		}
	}

	aat2870_enable(aat2870);

	for (i = 0; i < pdata->num_subdevs; i++) {
		for (j = 0; j < ARRAY_SIZE(aat2870_devs); j++) {
			if ((pdata->subdevs[i].id == aat2870_devs[j].id) &&
					!strcmp(pdata->subdevs[i].name,
						aat2870_devs[j].name)) {
				aat2870_devs[j].platform_data =
					pdata->subdevs[i].platform_data;
				break;
			}
		}
	}

	ret = mfd_add_devices(aat2870->dev, 0, aat2870_devs,
			      ARRAY_SIZE(aat2870_devs), NULL, 0, NULL);
	if (ret != 0) {
		dev_err(aat2870->dev, "Failed to add subdev: %d\n", ret);
		goto out_disable;
	}

	aat2870_init_debugfs(aat2870);

	return 0;

out_disable:
	aat2870_disable(aat2870);
	return ret;
}