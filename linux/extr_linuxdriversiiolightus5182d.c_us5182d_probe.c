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
struct us5182d_data {scalar_t__ default_continuous; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  US5182D_CFG0_SHUTDOWN_EN ; 
 int US5182D_CHIPID ; 
 int /*<<< orphan*/  US5182D_DRV_NAME ; 
 int /*<<< orphan*/  US5182D_REG_CHIPID ; 
 int /*<<< orphan*/  US5182D_SLEEP_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct us5182d_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  us5182d_channels ; 
 int us5182d_dark_gain_config (struct iio_dev*) ; 
 int /*<<< orphan*/  us5182d_get_platform_data (struct iio_dev*) ; 
 int /*<<< orphan*/  us5182d_info ; 
 int us5182d_init (struct iio_dev*) ; 
 int /*<<< orphan*/  us5182d_irq_thread_handler ; 
 int /*<<< orphan*/  us5182d_shutdown_en (struct us5182d_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int us5182d_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct us5182d_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &us5182d_info;
	indio_dev->name = US5182D_DRV_NAME;
	indio_dev->channels = us5182d_channels;
	indio_dev->num_channels = ARRAY_SIZE(us5182d_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = i2c_smbus_read_byte_data(data->client, US5182D_REG_CHIPID);
	if (ret != US5182D_CHIPID) {
		dev_err(&data->client->dev,
			"Failed to detect US5182 light chip\n");
		return (ret < 0) ? ret : -ENODEV;
	}

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq, NULL,
						us5182d_irq_thread_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"us5182d-irq", indio_dev);
		if (ret < 0)
			return ret;
	} else
		dev_warn(&client->dev, "no valid irq found\n");

	us5182d_get_platform_data(indio_dev);
	ret = us5182d_init(indio_dev);
	if (ret < 0)
		return ret;

	ret = us5182d_dark_gain_config(indio_dev);
	if (ret < 0)
		goto out_err;

	if (data->default_continuous) {
		ret = pm_runtime_set_active(&client->dev);
		if (ret < 0)
			goto out_err;
	}

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev,
					 US5182D_SLEEP_MS);
	pm_runtime_use_autosuspend(&client->dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto out_err;

	return 0;

out_err:
	us5182d_shutdown_en(data, US5182D_CFG0_SHUTDOWN_EN);
	return ret;

}