#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_6__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  id; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct bmg160_data {int irq; TYPE_3__* motion_trig; TYPE_3__* dready_trig; int /*<<< orphan*/  mutex; int /*<<< orphan*/  orientation; struct regmap* regmap; } ;
struct TYPE_7__ {struct device* parent; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMG160_AUTO_SUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  BMG160_IRQ_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  bmg160_accel_scan_masks ; 
 int /*<<< orphan*/  bmg160_buffer_setup_ops ; 
 int /*<<< orphan*/  bmg160_channels ; 
 int bmg160_chip_init (struct bmg160_data*) ; 
 int /*<<< orphan*/  bmg160_data_rdy_trig_poll ; 
 int /*<<< orphan*/  bmg160_event_handler ; 
 int /*<<< orphan*/  bmg160_info ; 
 char* bmg160_match_acpi_device (struct device*) ; 
 int /*<<< orphan*/  bmg160_trigger_handler ; 
 int /*<<< orphan*/  bmg160_trigger_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 void* devm_iio_trigger_alloc (struct device*,char*,char const*,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct bmg160_data* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (struct device*,char*,int /*<<< orphan*/ *) ; 
 int iio_trigger_register (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_trigger_set_drvdata (TYPE_3__*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

int bmg160_core_probe(struct device *dev, struct regmap *regmap, int irq,
		      const char *name)
{
	struct bmg160_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->irq = irq;
	data->regmap = regmap;

	ret = iio_read_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	if (ret)
		return ret;

	ret = bmg160_chip_init(data);
	if (ret < 0)
		return ret;

	mutex_init(&data->mutex);

	if (ACPI_HANDLE(dev))
		name = bmg160_match_acpi_device(dev);

	indio_dev->dev.parent = dev;
	indio_dev->channels = bmg160_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmg160_channels);
	indio_dev->name = name;
	indio_dev->available_scan_masks = bmg160_accel_scan_masks;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &bmg160_info;

	if (data->irq > 0) {
		ret = devm_request_threaded_irq(dev,
						data->irq,
						bmg160_data_rdy_trig_poll,
						bmg160_event_handler,
						IRQF_TRIGGER_RISING,
						BMG160_IRQ_NAME,
						indio_dev);
		if (ret)
			return ret;

		data->dready_trig = devm_iio_trigger_alloc(dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		if (!data->dready_trig)
			return -ENOMEM;

		data->motion_trig = devm_iio_trigger_alloc(dev,
							  "%s-any-motion-dev%d",
							  indio_dev->name,
							  indio_dev->id);
		if (!data->motion_trig)
			return -ENOMEM;

		data->dready_trig->dev.parent = dev;
		data->dready_trig->ops = &bmg160_trigger_ops;
		iio_trigger_set_drvdata(data->dready_trig, indio_dev);
		ret = iio_trigger_register(data->dready_trig);
		if (ret)
			return ret;

		data->motion_trig->dev.parent = dev;
		data->motion_trig->ops = &bmg160_trigger_ops;
		iio_trigger_set_drvdata(data->motion_trig, indio_dev);
		ret = iio_trigger_register(data->motion_trig);
		if (ret) {
			data->motion_trig = NULL;
			goto err_trigger_unregister;
		}
	}

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_time,
					 bmg160_trigger_handler,
					 &bmg160_buffer_setup_ops);
	if (ret < 0) {
		dev_err(dev,
			"iio triggered buffer setup failed\n");
		goto err_trigger_unregister;
	}

	ret = pm_runtime_set_active(dev);
	if (ret)
		goto err_buffer_cleanup;

	pm_runtime_enable(dev);
	pm_runtime_set_autosuspend_delay(dev,
					 BMG160_AUTO_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(dev, "unable to register iio device\n");
		goto err_buffer_cleanup;
	}

	return 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unregister:
	if (data->dready_trig)
		iio_trigger_unregister(data->dready_trig);
	if (data->motion_trig)
		iio_trigger_unregister(data->motion_trig);

	return ret;
}