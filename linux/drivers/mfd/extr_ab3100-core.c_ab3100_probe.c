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
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; scalar_t__ addr; int /*<<< orphan*/  adapter; } ;
struct ab3100_platform_data {int dummy; } ;
struct ab3100 {int chip_id; int /*<<< orphan*/  testreg_client; int /*<<< orphan*/ * chip_name; struct i2c_client* i2c_client; int /*<<< orphan*/ * dev; int /*<<< orphan*/  event_subscribers; int /*<<< orphan*/  access_mutex; } ;
struct TYPE_6__ {int id; char* name; } ;
struct TYPE_5__ {int pdata_size; struct ab3100_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_CID ; 
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* ab3100_devs ; 
 int ab3100_get_register_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ab3100_irq_handler ; 
 int /*<<< orphan*/  ab3100_ops ; 
 int ab3100_setup (struct ab3100*) ; 
 int /*<<< orphan*/  ab3100_setup_debugfs (struct ab3100*) ; 
 int abx500_register_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct ab3100_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 struct ab3100* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ab3100*) ; 
 int /*<<< orphan*/  i2c_new_dummy_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ab3100*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 TYPE_2__* ids ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*) ; 

__attribute__((used)) static int ab3100_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	struct ab3100 *ab3100;
	struct ab3100_platform_data *ab3100_plf_data =
		dev_get_platdata(&client->dev);
	int err;
	int i;

	ab3100 = devm_kzalloc(&client->dev, sizeof(struct ab3100), GFP_KERNEL);
	if (!ab3100)
		return -ENOMEM;

	/* Initialize data structure */
	mutex_init(&ab3100->access_mutex);
	BLOCKING_INIT_NOTIFIER_HEAD(&ab3100->event_subscribers);

	ab3100->i2c_client = client;
	ab3100->dev = &ab3100->i2c_client->dev;

	i2c_set_clientdata(client, ab3100);

	/* Read chip ID register */
	err = ab3100_get_register_interruptible(ab3100, AB3100_CID,
						&ab3100->chip_id);
	if (err) {
		dev_err(&client->dev,
			"failed to communicate with AB3100 chip\n");
		goto exit_no_detect;
	}

	for (i = 0; ids[i].id != 0x0; i++) {
		if (ids[i].id == ab3100->chip_id) {
			if (ids[i].name)
				break;

			dev_err(&client->dev, "AB3000 is not supported\n");
			goto exit_no_detect;
		}
	}

	snprintf(&ab3100->chip_name[0],
		 sizeof(ab3100->chip_name) - 1, "AB3100 %s", ids[i].name);

	if (ids[i].id == 0x0) {
		dev_err(&client->dev, "unknown analog baseband chip id: 0x%x\n",
			ab3100->chip_id);
		dev_err(&client->dev,
			"accepting it anyway. Please update the driver.\n");
		goto exit_no_detect;
	}

	dev_info(&client->dev, "Detected chip: %s\n",
		 &ab3100->chip_name[0]);

	/* Attach a second dummy i2c_client to the test register address */
	ab3100->testreg_client = i2c_new_dummy_device(client->adapter,
					       client->addr + 1);
	if (IS_ERR(ab3100->testreg_client)) {
		err = PTR_ERR(ab3100->testreg_client);
		goto exit_no_testreg_client;
	}

	err = ab3100_setup(ab3100);
	if (err)
		goto exit_no_setup;

	err = devm_request_threaded_irq(&client->dev,
					client->irq, NULL, ab3100_irq_handler,
					IRQF_ONESHOT, "ab3100-core", ab3100);
	if (err)
		goto exit_no_irq;

	err = abx500_register_ops(&client->dev, &ab3100_ops);
	if (err)
		goto exit_no_ops;

	/* Set up and register the platform devices. */
	for (i = 0; i < ARRAY_SIZE(ab3100_devs); i++) {
		ab3100_devs[i].platform_data = ab3100_plf_data;
		ab3100_devs[i].pdata_size = sizeof(struct ab3100_platform_data);
	}

	err = mfd_add_devices(&client->dev, 0, ab3100_devs,
			      ARRAY_SIZE(ab3100_devs), NULL, 0, NULL);

	ab3100_setup_debugfs(ab3100);

	return 0;

 exit_no_ops:
 exit_no_irq:
 exit_no_setup:
	i2c_unregister_device(ab3100->testreg_client);
 exit_no_testreg_client:
 exit_no_detect:
	return err;
}