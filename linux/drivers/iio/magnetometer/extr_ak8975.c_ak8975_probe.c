#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_15__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_2__* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  modes; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct i2c_device_id {char* name; scalar_t__ driver_data; } ;
struct TYPE_20__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct ak8975_platform_data {int eoc_gpio; int /*<<< orphan*/  orientation; } ;
struct ak8975_data {int eoc_gpio; int /*<<< orphan*/  lock; TYPE_15__* def; void* vid; void* vdd; int /*<<< orphan*/  orientation; scalar_t__ eoc_irq; struct i2c_client* client; } ;
typedef  enum asahi_compass_chipset { ____Placeholder_asahi_compass_chipset } asahi_compass_chipset ;
struct TYPE_18__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_2__*) ; 
 int AK_MAX_TYPE ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ak8975_channels ; 
 int /*<<< orphan*/  ak8975_handle_trigger ; 
 int /*<<< orphan*/  ak8975_info ; 
 char* ak8975_match_acpi_device (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  ak8975_power_off (struct ak8975_data*) ; 
 int ak8975_power_on (struct ak8975_data*) ; 
 int /*<<< orphan*/  ak8975_scan_masks ; 
 int ak8975_setup (struct i2c_client*) ; 
 int ak8975_who_i_am (struct i2c_client*,int /*<<< orphan*/ ) ; 
 TYPE_15__* ak_def_array ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct ak8975_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int devm_gpio_request_one (TYPE_2__*,int,int /*<<< orphan*/ ,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 void* devm_regulator_get (TYPE_2__*,char*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ak8975_data* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_get_gpio (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 

__attribute__((used)) static int ak8975_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ak8975_data *data;
	struct iio_dev *indio_dev;
	int eoc_gpio;
	int err;
	const char *name = NULL;
	enum asahi_compass_chipset chipset = AK_MAX_TYPE;
	const struct ak8975_platform_data *pdata =
		dev_get_platdata(&client->dev);

	/* Grab and set up the supplied GPIO. */
	if (pdata)
		eoc_gpio = pdata->eoc_gpio;
	else if (client->dev.of_node)
		eoc_gpio = of_get_gpio(client->dev.of_node, 0);
	else
		eoc_gpio = -1;

	if (eoc_gpio == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	/* We may not have a GPIO based IRQ to scan, that is fine, we will
	   poll if so */
	if (gpio_is_valid(eoc_gpio)) {
		err = devm_gpio_request_one(&client->dev, eoc_gpio,
							GPIOF_IN, "ak_8975");
		if (err < 0) {
			dev_err(&client->dev,
				"failed to request GPIO %d, error %d\n",
							eoc_gpio, err);
			return err;
		}
	}

	/* Register with IIO */
	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (indio_dev == NULL)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->client = client;
	data->eoc_gpio = eoc_gpio;
	data->eoc_irq = 0;

	if (!pdata) {
		err = iio_read_mount_matrix(&client->dev, "mount-matrix",
					    &data->orientation);
		if (err)
			return err;
	} else
		data->orientation = pdata->orientation;

	/* id will be NULL when enumerated via ACPI */
	if (id) {
		chipset = (enum asahi_compass_chipset)(id->driver_data);
		name = id->name;
	} else if (ACPI_HANDLE(&client->dev)) {
		name = ak8975_match_acpi_device(&client->dev, &chipset);
		if (!name)
			return -ENODEV;
	} else
		return -ENOSYS;

	if (chipset >= AK_MAX_TYPE) {
		dev_err(&client->dev, "AKM device type unsupported: %d\n",
			chipset);
		return -ENODEV;
	}

	data->def = &ak_def_array[chipset];

	/* Fetch the regulators */
	data->vdd = devm_regulator_get(&client->dev, "vdd");
	if (IS_ERR(data->vdd))
		return PTR_ERR(data->vdd);
	data->vid = devm_regulator_get(&client->dev, "vid");
	if (IS_ERR(data->vid))
		return PTR_ERR(data->vid);

	err = ak8975_power_on(data);
	if (err)
		return err;

	err = ak8975_who_i_am(client, data->def->type);
	if (err < 0) {
		dev_err(&client->dev, "Unexpected device\n");
		goto power_off;
	}
	dev_dbg(&client->dev, "Asahi compass chip %s\n", name);

	/* Perform some basic start-of-day setup of the device. */
	err = ak8975_setup(client);
	if (err < 0) {
		dev_err(&client->dev, "%s initialization fails\n", name);
		goto power_off;
	}

	mutex_init(&data->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->channels = ak8975_channels;
	indio_dev->num_channels = ARRAY_SIZE(ak8975_channels);
	indio_dev->info = &ak8975_info;
	indio_dev->available_scan_masks = ak8975_scan_masks;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->name = name;

	err = iio_triggered_buffer_setup(indio_dev, NULL, ak8975_handle_trigger,
					 NULL);
	if (err) {
		dev_err(&client->dev, "triggered buffer setup failed\n");
		goto power_off;
	}

	err = iio_device_register(indio_dev);
	if (err) {
		dev_err(&client->dev, "device register failed\n");
		goto cleanup_buffer;
	}

	/* Enable runtime PM */
	pm_runtime_get_noresume(&client->dev);
	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	/*
	 * The device comes online in 500us, so add two orders of magnitude
	 * of delay before autosuspending: 50 ms.
	 */
	pm_runtime_set_autosuspend_delay(&client->dev, 50);
	pm_runtime_use_autosuspend(&client->dev);
	pm_runtime_put(&client->dev);

	return 0;

cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
power_off:
	ak8975_power_off(data);
	return err;
}