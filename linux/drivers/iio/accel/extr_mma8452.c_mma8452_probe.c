#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {int /*<<< orphan*/  compatible; TYPE_2__* data; } ;
struct mma8452_data {int data_cfg; int ctrl_reg1; void* vdd_reg; void* vddio_reg; int /*<<< orphan*/  sleep_val; TYPE_2__* chip_info; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_14__ {TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  available_scan_masks; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int irq; TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int chip_id; int all_events; int enabled_events; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
#define  FXLS8471_DEVICE_ID 133 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
#define  MMA8451_DEVICE_ID 132 
 int /*<<< orphan*/  MMA8452_AUTO_SUSPEND_DELAY_MS ; 
 int MMA8452_CTRL_ACTIVE ; 
 int MMA8452_CTRL_DR_DEFAULT ; 
 int MMA8452_CTRL_DR_SHIFT ; 
 int /*<<< orphan*/  MMA8452_CTRL_REG1 ; 
 int /*<<< orphan*/  MMA8452_CTRL_REG4 ; 
 int /*<<< orphan*/  MMA8452_CTRL_REG5 ; 
 int /*<<< orphan*/  MMA8452_DATA_CFG ; 
 int MMA8452_DATA_CFG_FS_2G ; 
#define  MMA8452_DEVICE_ID 131 
 int /*<<< orphan*/  MMA8452_TRANSIENT_THS ; 
 int MMA8452_TRANSIENT_THS_MASK ; 
 int /*<<< orphan*/  MMA8452_WHO_AM_I ; 
#define  MMA8453_DEVICE_ID 130 
#define  MMA8652_DEVICE_ID 129 
#define  MMA8653_DEVICE_ID 128 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 int devm_request_threaded_irq (TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mma8452_calculate_sleep (struct mma8452_data*) ; 
 int /*<<< orphan*/  mma8452_dt_ids ; 
 int /*<<< orphan*/  mma8452_info ; 
 int /*<<< orphan*/  mma8452_interrupt ; 
 int mma8452_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  mma8452_scan_masks ; 
 int mma8452_set_freefall_mode (struct mma8452_data*,int) ; 
 int /*<<< orphan*/  mma8452_trigger_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  mma8452_trigger_handler ; 
 int mma8452_trigger_setup (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_irq_get_byname (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int pm_runtime_set_active (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_3__*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 

__attribute__((used)) static int mma8452_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct mma8452_data *data;
	struct iio_dev *indio_dev;
	int ret;
	const struct of_device_id *match;

	match = of_match_device(mma8452_dt_ids, &client->dev);
	if (!match) {
		dev_err(&client->dev, "unknown device model\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);
	data->chip_info = match->data;

	data->vdd_reg = devm_regulator_get(&client->dev, "vdd");
	if (IS_ERR(data->vdd_reg)) {
		if (PTR_ERR(data->vdd_reg) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(&client->dev, "failed to get VDD regulator!\n");
		return PTR_ERR(data->vdd_reg);
	}

	data->vddio_reg = devm_regulator_get(&client->dev, "vddio");
	if (IS_ERR(data->vddio_reg)) {
		if (PTR_ERR(data->vddio_reg) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_err(&client->dev, "failed to get VDDIO regulator!\n");
		return PTR_ERR(data->vddio_reg);
	}

	ret = regulator_enable(data->vdd_reg);
	if (ret) {
		dev_err(&client->dev, "failed to enable VDD regulator!\n");
		return ret;
	}

	ret = regulator_enable(data->vddio_reg);
	if (ret) {
		dev_err(&client->dev, "failed to enable VDDIO regulator!\n");
		goto disable_regulator_vdd;
	}

	ret = i2c_smbus_read_byte_data(client, MMA8452_WHO_AM_I);
	if (ret < 0)
		goto disable_regulators;

	switch (ret) {
	case MMA8451_DEVICE_ID:
	case MMA8452_DEVICE_ID:
	case MMA8453_DEVICE_ID:
	case MMA8652_DEVICE_ID:
	case MMA8653_DEVICE_ID:
	case FXLS8471_DEVICE_ID:
		if (ret == data->chip_info->chip_id)
			break;
		/* fall through */
	default:
		ret = -ENODEV;
		goto disable_regulators;
	}

	dev_info(&client->dev, "registering %s accelerometer; ID 0x%x\n",
		 match->compatible, data->chip_info->chip_id);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &mma8452_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = data->chip_info->channels;
	indio_dev->num_channels = data->chip_info->num_channels;
	indio_dev->available_scan_masks = mma8452_scan_masks;

	ret = mma8452_reset(client);
	if (ret < 0)
		goto disable_regulators;

	data->data_cfg = MMA8452_DATA_CFG_FS_2G;
	ret = i2c_smbus_write_byte_data(client, MMA8452_DATA_CFG,
					data->data_cfg);
	if (ret < 0)
		goto disable_regulators;

	/*
	 * By default set transient threshold to max to avoid events if
	 * enabling without configuring threshold.
	 */
	ret = i2c_smbus_write_byte_data(client, MMA8452_TRANSIENT_THS,
					MMA8452_TRANSIENT_THS_MASK);
	if (ret < 0)
		goto disable_regulators;

	if (client->irq) {
		int irq2;

		irq2 = of_irq_get_byname(client->dev.of_node, "INT2");

		if (irq2 == client->irq) {
			dev_dbg(&client->dev, "using interrupt line INT2\n");
		} else {
			ret = i2c_smbus_write_byte_data(client,
						MMA8452_CTRL_REG5,
						data->chip_info->all_events);
			if (ret < 0)
				goto disable_regulators;

			dev_dbg(&client->dev, "using interrupt line INT1\n");
		}

		ret = i2c_smbus_write_byte_data(client,
					MMA8452_CTRL_REG4,
					data->chip_info->enabled_events);
		if (ret < 0)
			goto disable_regulators;

		ret = mma8452_trigger_setup(indio_dev);
		if (ret < 0)
			goto disable_regulators;
	}

	data->ctrl_reg1 = MMA8452_CTRL_ACTIVE |
			  (MMA8452_CTRL_DR_DEFAULT << MMA8452_CTRL_DR_SHIFT);

	data->sleep_val = mma8452_calculate_sleep(data);

	ret = i2c_smbus_write_byte_data(client, MMA8452_CTRL_REG1,
					data->ctrl_reg1);
	if (ret < 0)
		goto trigger_cleanup;

	ret = iio_triggered_buffer_setup(indio_dev, NULL,
					 mma8452_trigger_handler, NULL);
	if (ret < 0)
		goto trigger_cleanup;

	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev,
						client->irq,
						NULL, mma8452_interrupt,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, indio_dev);
		if (ret)
			goto buffer_cleanup;
	}

	ret = pm_runtime_set_active(&client->dev);
	if (ret < 0)
		goto buffer_cleanup;

	pm_runtime_enable(&client->dev);
	pm_runtime_set_autosuspend_delay(&client->dev,
					 MMA8452_AUTO_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto buffer_cleanup;

	ret = mma8452_set_freefall_mode(data, false);
	if (ret < 0)
		goto buffer_cleanup;

	return 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);

trigger_cleanup:
	mma8452_trigger_cleanup(indio_dev);

disable_regulators:
	regulator_disable(data->vddio_reg);

disable_regulator_vdd:
	regulator_disable(data->vdd_reg);

	return ret;
}