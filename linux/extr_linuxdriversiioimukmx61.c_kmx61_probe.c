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
struct kmx61_data {void* acc_dready_trig; void* mag_dready_trig; void* motion_trig; void* acc_indio_dev; void* mag_indio_dev; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {char* name; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int KMX61_ACC ; 
 int /*<<< orphan*/  KMX61_ALL_STBY ; 
 int /*<<< orphan*/  KMX61_IRQ_NAME ; 
 int KMX61_MAG ; 
 int /*<<< orphan*/  KMX61_SLEEP_DELAY_MS ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct kmx61_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kmx61_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct kmx61_data*) ; 
 int iio_device_register (void*) ; 
 int /*<<< orphan*/  iio_device_unregister (void*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 int /*<<< orphan*/  iio_trigger_unregister (void*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (void*) ; 
 int iio_triggered_buffer_setup (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmx61_acc_channels ; 
 int /*<<< orphan*/  kmx61_acc_info ; 
 int kmx61_chip_init (struct kmx61_data*) ; 
 int /*<<< orphan*/  kmx61_data_rdy_trig_poll ; 
 int /*<<< orphan*/  kmx61_event_handler ; 
 void* kmx61_indiodev_setup (struct kmx61_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kmx61_mag_channels ; 
 int /*<<< orphan*/  kmx61_mag_info ; 
 char* kmx61_match_acpi_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmx61_set_mode (struct kmx61_data*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kmx61_trigger_handler ; 
 void* kmx61_trigger_setup (struct kmx61_data*,void*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kmx61_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	int ret;
	struct kmx61_data *data;
	const char *name = NULL;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;

	mutex_init(&data->lock);

	if (id)
		name = id->name;
	else if (ACPI_HANDLE(&client->dev))
		name = kmx61_match_acpi_device(&client->dev);
	else
		return -ENODEV;

	data->acc_indio_dev =
		kmx61_indiodev_setup(data, &kmx61_acc_info,
				     kmx61_acc_channels,
				     ARRAY_SIZE(kmx61_acc_channels),
				     name);
	if (IS_ERR(data->acc_indio_dev))
		return PTR_ERR(data->acc_indio_dev);

	data->mag_indio_dev =
		kmx61_indiodev_setup(data, &kmx61_mag_info,
				     kmx61_mag_channels,
				     ARRAY_SIZE(kmx61_mag_channels),
				     name);
	if (IS_ERR(data->mag_indio_dev))
		return PTR_ERR(data->mag_indio_dev);

	ret = kmx61_chip_init(data);
	if (ret < 0)
		return ret;

	if (client->irq > 0) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
						kmx61_data_rdy_trig_poll,
						kmx61_event_handler,
						IRQF_TRIGGER_RISING,
						KMX61_IRQ_NAME,
						data);
		if (ret)
			goto err_chip_uninit;

		data->acc_dready_trig =
			kmx61_trigger_setup(data, data->acc_indio_dev,
					    "dready");
		if (IS_ERR(data->acc_dready_trig)) {
			ret = PTR_ERR(data->acc_dready_trig);
			goto err_chip_uninit;
		}

		data->mag_dready_trig =
			kmx61_trigger_setup(data, data->mag_indio_dev,
					    "dready");
		if (IS_ERR(data->mag_dready_trig)) {
			ret = PTR_ERR(data->mag_dready_trig);
			goto err_trigger_unregister_acc_dready;
		}

		data->motion_trig =
			kmx61_trigger_setup(data, data->acc_indio_dev,
					    "any-motion");
		if (IS_ERR(data->motion_trig)) {
			ret = PTR_ERR(data->motion_trig);
			goto err_trigger_unregister_mag_dready;
		}

		ret = iio_triggered_buffer_setup(data->acc_indio_dev,
						 &iio_pollfunc_store_time,
						 kmx61_trigger_handler,
						 NULL);
		if (ret < 0) {
			dev_err(&data->client->dev,
				"Failed to setup acc triggered buffer\n");
			goto err_trigger_unregister_motion;
		}

		ret = iio_triggered_buffer_setup(data->mag_indio_dev,
						 &iio_pollfunc_store_time,
						 kmx61_trigger_handler,
						 NULL);
		if (ret < 0) {
			dev_err(&data->client->dev,
				"Failed to setup mag triggered buffer\n");
			goto err_buffer_cleanup_acc;
		}
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0)
		goto err_buffer_cleanup_mag;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev, KMX61_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	ret = iio_device_register(data->acc_indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to register acc iio device\n");
		goto err_buffer_cleanup_mag;
	}

	ret = iio_device_register(data->mag_indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to register mag iio device\n");
		goto err_iio_unregister_acc;
	}

	return 0;

err_iio_unregister_acc:
	iio_device_unregister(data->acc_indio_dev);
err_buffer_cleanup_mag:
	if (client->irq > 0)
		iio_triggered_buffer_cleanup(data->mag_indio_dev);
err_buffer_cleanup_acc:
	if (client->irq > 0)
		iio_triggered_buffer_cleanup(data->acc_indio_dev);
err_trigger_unregister_motion:
	iio_trigger_unregister(data->motion_trig);
err_trigger_unregister_mag_dready:
	iio_trigger_unregister(data->mag_dready_trig);
err_trigger_unregister_acc_dready:
	iio_trigger_unregister(data->acc_dready_trig);
err_chip_uninit:
	kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	return ret;
}