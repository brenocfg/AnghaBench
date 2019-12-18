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
struct mma9553_data {int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {char const* name; TYPE_1__ dev; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;
struct i2c_device_id {char* name; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  MMA9551_AUTO_SUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  MMA9553_IRQ_NAME ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mma9553_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mma9551_set_device_state (struct i2c_client*,int) ; 
 int /*<<< orphan*/  mma9553_channels ; 
 int /*<<< orphan*/  mma9553_event_handler ; 
 int /*<<< orphan*/  mma9553_info ; 
 int mma9553_init (struct mma9553_data*) ; 
 int /*<<< orphan*/  mma9553_init_events (struct mma9553_data*) ; 
 int /*<<< orphan*/  mma9553_irq_handler ; 
 char* mma9553_match_acpi_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mma9553_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct mma9553_data *data;
	struct iio_dev *indio_dev;
	const char *name = NULL;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	if (id)
		name = id->name;
	else if (ACPI_HANDLE(&client->dev))
		name = mma9553_match_acpi_device(&client->dev);
	else
		return -ENOSYS;

	mutex_init(&data->mutex);
	mma9553_init_events(data);

	ret = mma9553_init(data);
	if (ret < 0)
		return ret;

	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = mma9553_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma9553_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mma9553_info;

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						mma9553_irq_handler,
						mma9553_event_handler,
						IRQF_TRIGGER_RISING,
						MMA9553_IRQ_NAME, indio_dev);
		if (ret < 0) {
			dev_err(&client->dev, "request irq %d failed\n",
				client->irq);
			goto out_poweroff;
		}
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0)
		goto out_poweroff;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev,
					 MMA9551_AUTO_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "unable to register iio device\n");
		goto out_poweroff;
	}

	dev_dbg(&indio_dev->dev, "Registered device %s\n", name);
	return 0;

out_poweroff:
	mma9551_set_device_state(client, false);
	return ret;
}