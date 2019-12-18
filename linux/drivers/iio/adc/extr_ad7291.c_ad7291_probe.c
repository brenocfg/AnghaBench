#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; struct ad7291_platform_data* platform_data; } ;
struct i2c_client {scalar_t__ irq; TYPE_2__ dev; } ;
struct ad7291_platform_data {scalar_t__ use_external_ref; } ;
struct ad7291_chip_info {int command; scalar_t__ reg; struct i2c_client* client; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int AD7291_ALERT_POLARITY ; 
 int /*<<< orphan*/  AD7291_COMMAND ; 
 int AD7291_EXT_REF ; 
 int AD7291_NOISE_DELAY ; 
 int AD7291_RESET ; 
 int AD7291_T_SENSE_MASK ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  ad7291_channels ; 
 int /*<<< orphan*/  ad7291_event_handler ; 
 int ad7291_i2c_write (struct ad7291_chip_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ad7291_info ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 scalar_t__ devm_regulator_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ad7291_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int request_threaded_irq (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct iio_dev*) ; 

__attribute__((used)) static int ad7291_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ad7291_platform_data *pdata = client->dev.platform_data;
	struct ad7291_chip_info *chip;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);

	if (pdata && pdata->use_external_ref) {
		chip->reg = devm_regulator_get(&client->dev, "vref");
		if (IS_ERR(chip->reg))
			return PTR_ERR(chip->reg);

		ret = regulator_enable(chip->reg);
		if (ret)
			return ret;
	}

	mutex_init(&chip->state_lock);
	/* this is only used for device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;

	chip->command = AD7291_NOISE_DELAY |
			AD7291_T_SENSE_MASK | /* Tsense always enabled */
			AD7291_ALERT_POLARITY; /* set irq polarity low level */

	if (pdata && pdata->use_external_ref)
		chip->command |= AD7291_EXT_REF;

	indio_dev->name = id->name;
	indio_dev->channels = ad7291_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7291_channels);

	indio_dev->dev.parent = &client->dev;
	indio_dev->dev.of_node = client->dev.of_node;
	indio_dev->info = &ad7291_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = ad7291_i2c_write(chip, AD7291_COMMAND, AD7291_RESET);
	if (ret) {
		ret = -EIO;
		goto error_disable_reg;
	}

	ret = ad7291_i2c_write(chip, AD7291_COMMAND, chip->command);
	if (ret) {
		ret = -EIO;
		goto error_disable_reg;
	}

	if (client->irq > 0) {
		ret = request_threaded_irq(client->irq,
					   NULL,
					   &ad7291_event_handler,
					   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					   id->name,
					   indio_dev);
		if (ret)
			goto error_disable_reg;
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto error_unreg_irq;

	return 0;

error_unreg_irq:
	if (client->irq)
		free_irq(client->irq, indio_dev);
error_disable_reg:
	if (chip->reg)
		regulator_disable(chip->reg);

	return ret;
}