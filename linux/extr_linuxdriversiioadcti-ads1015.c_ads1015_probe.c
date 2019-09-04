#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ of_node; TYPE_5__* parent; } ;
struct iio_dev {TYPE_3__* channels; int /*<<< orphan*/ * info; void* num_channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_18__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_5__ dev; int /*<<< orphan*/  name; scalar_t__ irq; } ;
struct ads1015_data {unsigned int* data_rate; int event_channel; int conv_invalid; int /*<<< orphan*/  regmap; TYPE_4__* thresh_data; int /*<<< orphan*/  lock; } ;
typedef  enum chip_ids { ____Placeholder_chip_ids } chip_ids ;
struct TYPE_17__ {int low_thresh; int high_thresh; } ;
struct TYPE_15__ {int realbits; } ;
struct TYPE_16__ {TYPE_2__ scan_type; } ;

/* Variables and functions */
#define  ADS1015 131 
 int ADS1015_CFG_COMP_DISABLE ; 
 unsigned int ADS1015_CFG_COMP_LAT_MASK ; 
 int ADS1015_CFG_COMP_LAT_SHIFT ; 
 unsigned int ADS1015_CFG_COMP_POL_HIGH ; 
 unsigned int ADS1015_CFG_COMP_POL_LOW ; 
 unsigned int ADS1015_CFG_COMP_POL_MASK ; 
 unsigned int ADS1015_CFG_COMP_POL_SHIFT ; 
 unsigned int ADS1015_CFG_COMP_QUE_MASK ; 
 int ADS1015_CFG_COMP_QUE_SHIFT ; 
 int /*<<< orphan*/  ADS1015_CFG_REG ; 
 int ADS1015_CHANNELS ; 
 int /*<<< orphan*/  ADS1015_CONTINUOUS ; 
 int /*<<< orphan*/  ADS1015_DRV_NAME ; 
 int /*<<< orphan*/  ADS1015_SLEEP_DELAY_MS ; 
#define  ADS1115 130 
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 unsigned long IRQF_ONESHOT ; 
#define  IRQF_TRIGGER_HIGH 129 
#define  IRQF_TRIGGER_LOW 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads1015_buffer_setup_ops ; 
 void* ads1015_channels ; 
 int /*<<< orphan*/  ads1015_data_rate ; 
 int /*<<< orphan*/  ads1015_event_handler ; 
 int /*<<< orphan*/  ads1015_get_channels_config (struct i2c_client*) ; 
 int /*<<< orphan*/  ads1015_info ; 
 int /*<<< orphan*/  ads1015_regmap_config ; 
 int ads1015_set_conv_mode (struct ads1015_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ads1015_trigger_handler ; 
 void* ads1115_channels ; 
 int /*<<< orphan*/  ads1115_data_rate ; 
 int /*<<< orphan*/  ads1115_info ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_5__*,int) ; 
 int devm_iio_triggered_buffer_setup (TYPE_5__*,struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (TYPE_5__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ads1015_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  irq_get_irq_data (scalar_t__) ; 
 unsigned long irqd_get_trigger_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_5__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_5__*) ; 
 int pm_runtime_set_active (TYPE_5__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_5__*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int ads1015_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ads1015_data *data;
	int ret;
	enum chip_ids chip;
	int i;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->dev.of_node = client->dev.of_node;
	indio_dev->name = ADS1015_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (client->dev.of_node)
		chip = (enum chip_ids)of_device_get_match_data(&client->dev);
	else
		chip = id->driver_data;
	switch (chip) {
	case ADS1015:
		indio_dev->channels = ads1015_channels;
		indio_dev->num_channels = ARRAY_SIZE(ads1015_channels);
		indio_dev->info = &ads1015_info;
		data->data_rate = (unsigned int *) &ads1015_data_rate;
		break;
	case ADS1115:
		indio_dev->channels = ads1115_channels;
		indio_dev->num_channels = ARRAY_SIZE(ads1115_channels);
		indio_dev->info = &ads1115_info;
		data->data_rate = (unsigned int *) &ads1115_data_rate;
		break;
	}

	data->event_channel = ADS1015_CHANNELS;
	/*
	 * Set default lower and upper threshold to min and max value
	 * respectively.
	 */
	for (i = 0; i < ADS1015_CHANNELS; i++) {
		int realbits = indio_dev->channels[i].scan_type.realbits;

		data->thresh_data[i].low_thresh = -1 << (realbits - 1);
		data->thresh_data[i].high_thresh = (1 << (realbits - 1)) - 1;
	}

	/* we need to keep this ABI the same as used by hwmon ADS1015 driver */
	ads1015_get_channels_config(client);

	data->regmap = devm_regmap_init_i2c(client, &ads1015_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(&client->dev, "Failed to allocate register map\n");
		return PTR_ERR(data->regmap);
	}

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev, NULL,
					      ads1015_trigger_handler,
					      &ads1015_buffer_setup_ops);
	if (ret < 0) {
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		return ret;
	}

	if (client->irq) {
		unsigned long irq_trig =
			irqd_get_trigger_type(irq_get_irq_data(client->irq));
		unsigned int cfg_comp_mask = ADS1015_CFG_COMP_QUE_MASK |
			ADS1015_CFG_COMP_LAT_MASK | ADS1015_CFG_COMP_POL_MASK;
		unsigned int cfg_comp =
			ADS1015_CFG_COMP_DISABLE << ADS1015_CFG_COMP_QUE_SHIFT |
			1 << ADS1015_CFG_COMP_LAT_SHIFT;

		switch (irq_trig) {
		case IRQF_TRIGGER_LOW:
			cfg_comp |= ADS1015_CFG_COMP_POL_LOW <<
					ADS1015_CFG_COMP_POL_SHIFT;
			break;
		case IRQF_TRIGGER_HIGH:
			cfg_comp |= ADS1015_CFG_COMP_POL_HIGH <<
					ADS1015_CFG_COMP_POL_SHIFT;
			break;
		default:
			return -EINVAL;
		}

		ret = regmap_update_bits(data->regmap, ADS1015_CFG_REG,
					cfg_comp_mask, cfg_comp);
		if (ret)
			return ret;

		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL, ads1015_event_handler,
						irq_trig | IRQF_ONESHOT,
						client->name, indio_dev);
		if (ret)
			return ret;
	}

	ret = ads1015_set_conv_mode(data, ADS1015_CONTINUOUS);
	if (ret)
		return ret;

	data->conv_invalid = true;

	ret = pm_runtime_set_active(&client->dev);
	if (ret)
		return ret;
	pm_runtime_set_autosuspend_delay(&client->dev, ADS1015_SLEEP_DELAY_MS);
	pm_runtime_use_autosuspend(&client->dev);
	pm_runtime_enable(&client->dev);

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to register IIO device\n");
		return ret;
	}

	return 0;
}