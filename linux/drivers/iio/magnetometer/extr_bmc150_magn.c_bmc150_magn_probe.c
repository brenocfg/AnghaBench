#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct TYPE_9__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  id; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct bmc150_magn_data {int irq; TYPE_3__* dready_trig; int /*<<< orphan*/  mutex; int /*<<< orphan*/  orientation; struct device* dev; struct regmap* regmap; } ;
struct TYPE_10__ {struct device* parent; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; TYPE_2__ dev; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMC150_MAGN_AUTO_SUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  BMC150_MAGN_IRQ_NAME ; 
 int /*<<< orphan*/  BMC150_MAGN_POWER_MODE_SUSPEND ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  bmc150_magn_buffer_setup_ops ; 
 int /*<<< orphan*/  bmc150_magn_channels ; 
 int /*<<< orphan*/  bmc150_magn_info ; 
 int bmc150_magn_init (struct bmc150_magn_data*) ; 
 char* bmc150_magn_match_acpi_device (struct device*) ; 
 int /*<<< orphan*/  bmc150_magn_scan_masks ; 
 int /*<<< orphan*/  bmc150_magn_set_power_mode (struct bmc150_magn_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bmc150_magn_trigger_handler ; 
 int /*<<< orphan*/  bmc150_magn_trigger_ops ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 TYPE_3__* devm_iio_trigger_alloc (struct device*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int,TYPE_3__*) ; 
 int iio_device_register (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 int iio_read_mount_matrix (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_trigger_generic_data_rdy_poll ; 
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
 int request_threaded_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 

int bmc150_magn_probe(struct device *dev, struct regmap *regmap,
		      int irq, const char *name)
{
	struct bmc150_magn_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	data->irq = irq;
	data->dev = dev;

	ret = iio_read_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	if (ret)
		return ret;

	if (!name && ACPI_HANDLE(dev))
		name = bmc150_magn_match_acpi_device(dev);

	mutex_init(&data->mutex);

	ret = bmc150_magn_init(data);
	if (ret < 0)
		return ret;

	indio_dev->dev.parent = dev;
	indio_dev->channels = bmc150_magn_channels;
	indio_dev->num_channels = ARRAY_SIZE(bmc150_magn_channels);
	indio_dev->available_scan_masks = bmc150_magn_scan_masks;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &bmc150_magn_info;

	if (irq > 0) {
		data->dready_trig = devm_iio_trigger_alloc(dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		if (!data->dready_trig) {
			ret = -ENOMEM;
			dev_err(dev, "iio trigger alloc failed\n");
			goto err_poweroff;
		}

		data->dready_trig->dev.parent = dev;
		data->dready_trig->ops = &bmc150_magn_trigger_ops;
		iio_trigger_set_drvdata(data->dready_trig, indio_dev);
		ret = iio_trigger_register(data->dready_trig);
		if (ret) {
			dev_err(dev, "iio trigger register failed\n");
			goto err_poweroff;
		}

		ret = request_threaded_irq(irq,
					   iio_trigger_generic_data_rdy_poll,
					   NULL,
					   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					   BMC150_MAGN_IRQ_NAME,
					   data->dready_trig);
		if (ret < 0) {
			dev_err(dev, "request irq %d failed\n", irq);
			goto err_trigger_unregister;
		}
	}

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_time,
					 bmc150_magn_trigger_handler,
					 &bmc150_magn_buffer_setup_ops);
	if (ret < 0) {
		dev_err(dev, "iio triggered buffer setup failed\n");
		goto err_free_irq;
	}

	ret = pm_runtime_set_active(dev);
	if (ret)
		goto err_buffer_cleanup;

	pm_runtime_enable(dev);
	pm_runtime_set_autosuspend_delay(dev,
					 BMC150_MAGN_AUTO_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(dev, "unable to register iio device\n");
		goto err_buffer_cleanup;
	}

	dev_dbg(dev, "Registered device %s\n", name);
	return 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_free_irq:
	if (irq > 0)
		free_irq(irq, data->dready_trig);
err_trigger_unregister:
	if (data->dready_trig)
		iio_trigger_unregister(data->dready_trig);
err_poweroff:
	bmc150_magn_set_power_mode(data, BMC150_MAGN_POWER_MODE_SUSPEND, true);
	return ret;
}