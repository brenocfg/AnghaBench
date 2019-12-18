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
struct tmp007_data {int config; int status_mask; struct i2c_client* client; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  TMP007_CONFIG ; 
 int TMP007_CONFIG_ALERT_EN ; 
 int TMP007_CONFIG_CONV_EN ; 
 int TMP007_CONFIG_TC_EN ; 
 int TMP007_STATUS_LHF ; 
 int TMP007_STATUS_LLF ; 
 int /*<<< orphan*/  TMP007_STATUS_MASK ; 
 int TMP007_STATUS_OHF ; 
 int TMP007_STATUS_OLF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct tmp007_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp007_channels ; 
 int /*<<< orphan*/  tmp007_identify (struct i2c_client*) ; 
 int /*<<< orphan*/  tmp007_info ; 
 int /*<<< orphan*/  tmp007_interrupt_handler ; 
 int /*<<< orphan*/  tmp007_powerdown (struct tmp007_data*) ; 

__attribute__((used)) static int tmp007_probe(struct i2c_client *client,
			const struct i2c_device_id *tmp007_id)
{
	struct tmp007_data *data;
	struct iio_dev *indio_dev;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		return -EOPNOTSUPP;

	if (!tmp007_identify(client)) {
		dev_err(&client->dev, "TMP007 not found\n");
		return -ENODEV;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = "tmp007";
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &tmp007_info;

	indio_dev->channels = tmp007_channels;
	indio_dev->num_channels = ARRAY_SIZE(tmp007_channels);

	/*
	 * Set Configuration register:
	 * 1. Conversion ON
	 * 2. ALERT enable
	 * 3. Transient correction enable
	 */

	ret = i2c_smbus_read_word_swapped(data->client, TMP007_CONFIG);
	if (ret < 0)
		return ret;

	data->config = ret;
	data->config |= (TMP007_CONFIG_CONV_EN | TMP007_CONFIG_ALERT_EN | TMP007_CONFIG_TC_EN);

	ret = i2c_smbus_write_word_swapped(data->client, TMP007_CONFIG,
					data->config);
	if (ret < 0)
		return ret;

	/*
	 * Only the following flags can activate ALERT pin. Data conversion/validity flags
	 * flags can still be polled for getting temperature data
	 *
	 * Set Status Mask register:
	 * 1. Object temperature high limit enable
	 * 2. Object temperature low limit enable
	 * 3. TDIE temperature high limit enable
	 * 4. TDIE temperature low limit enable
	 */

	ret = i2c_smbus_read_word_swapped(data->client, TMP007_STATUS_MASK);
	if (ret < 0)
		goto error_powerdown;

	data->status_mask = ret;
	data->status_mask |= (TMP007_STATUS_OHF | TMP007_STATUS_OLF
				| TMP007_STATUS_LHF | TMP007_STATUS_LLF);

	ret = i2c_smbus_write_word_swapped(data->client, TMP007_STATUS_MASK, data->status_mask);
	if (ret < 0)
		goto error_powerdown;

	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
				NULL, tmp007_interrupt_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				tmp007_id->name, indio_dev);
		if (ret) {
			dev_err(&client->dev, "irq request error %d\n", -ret);
			goto error_powerdown;
		}
	}

	return iio_device_register(indio_dev);

error_powerdown:
	tmp007_powerdown(data);

	return ret;
}