#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ina2xx_platform_data {unsigned int shunt_uohms; } ;
struct ina2xx_chip_info {int avg; TYPE_2__* config; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  regmap; } ;
struct TYPE_9__ {scalar_t__ of_node; TYPE_1__* parent; } ;
struct iio_dev {int modes; TYPE_3__ dev; int /*<<< orphan*/ * setup_ops; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; void* num_channels; void* channels; } ;
struct iio_buffer {int dummy; } ;
struct i2c_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
typedef  enum ina2xx_ids { ____Placeholder_ina2xx_ids } ina2xx_ids ;
struct TYPE_8__ {unsigned int config_default; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INA219_DEFAULT_BRNG ; 
 int /*<<< orphan*/  INA219_DEFAULT_IT ; 
 int /*<<< orphan*/  INA219_DEFAULT_PGA ; 
 int /*<<< orphan*/  INA226_DEFAULT_AVG ; 
 int /*<<< orphan*/  INA226_DEFAULT_IT ; 
 unsigned int INA2XX_RSHUNT_DEFAULT ; 
 int INDIO_BUFFER_SOFTWARE ; 
 int INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct ina2xx_platform_data* dev_get_platdata (TYPE_1__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_1__*,int) ; 
 struct iio_buffer* devm_iio_kfifo_allocate (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_attach_buffer (struct iio_dev*,struct iio_buffer*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ina2xx_chip_info* iio_priv (struct iio_dev*) ; 
 void* ina219_channels ; 
 int /*<<< orphan*/  ina219_info ; 
 int /*<<< orphan*/  ina219_set_int_time_vbus (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ina219_set_int_time_vshunt (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ina219_set_vbus_range_denom (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ina219_set_vshunt_pga_gain (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ ina226 ; 
 void* ina226_channels ; 
 int /*<<< orphan*/  ina226_info ; 
 int /*<<< orphan*/  ina226_set_average (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ina226_set_int_time_vbus (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ina226_set_int_time_vshunt (struct ina2xx_chip_info*,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_2__* ina2xx_config ; 
 int ina2xx_init (struct ina2xx_chip_info*,unsigned int) ; 
 int /*<<< orphan*/  ina2xx_regmap_config ; 
 int /*<<< orphan*/  ina2xx_setup_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 scalar_t__ of_property_read_u32 (scalar_t__,char*,unsigned int*) ; 
 int set_shunt_resistor (struct ina2xx_chip_info*,unsigned int) ; 

__attribute__((used)) static int ina2xx_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ina2xx_chip_info *chip;
	struct iio_dev *indio_dev;
	struct iio_buffer *buffer;
	unsigned int val;
	enum ina2xx_ids type;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;

	chip = iio_priv(indio_dev);

	/* This is only used for device removal purposes. */
	i2c_set_clientdata(client, indio_dev);

	chip->regmap = devm_regmap_init_i2c(client, &ina2xx_regmap_config);
	if (IS_ERR(chip->regmap)) {
		dev_err(&client->dev, "failed to allocate register map\n");
		return PTR_ERR(chip->regmap);
	}

	if (client->dev.of_node)
		type = (enum ina2xx_ids)of_device_get_match_data(&client->dev);
	else
		type = id->driver_data;
	chip->config = &ina2xx_config[type];

	mutex_init(&chip->state_lock);

	if (of_property_read_u32(client->dev.of_node,
				 "shunt-resistor", &val) < 0) {
		struct ina2xx_platform_data *pdata =
		    dev_get_platdata(&client->dev);

		if (pdata)
			val = pdata->shunt_uohms;
		else
			val = INA2XX_RSHUNT_DEFAULT;
	}

	ret = set_shunt_resistor(chip, val);
	if (ret)
		return ret;

	/* Patch the current config register with default. */
	val = chip->config->config_default;

	if (id->driver_data == ina226) {
		ina226_set_average(chip, INA226_DEFAULT_AVG, &val);
		ina226_set_int_time_vbus(chip, INA226_DEFAULT_IT, &val);
		ina226_set_int_time_vshunt(chip, INA226_DEFAULT_IT, &val);
	} else {
		chip->avg = 1;
		ina219_set_int_time_vbus(chip, INA219_DEFAULT_IT, &val);
		ina219_set_int_time_vshunt(chip, INA219_DEFAULT_IT, &val);
		ina219_set_vbus_range_denom(chip, INA219_DEFAULT_BRNG, &val);
		ina219_set_vshunt_pga_gain(chip, INA219_DEFAULT_PGA, &val);
	}

	ret = ina2xx_init(chip, val);
	if (ret) {
		dev_err(&client->dev, "error configuring the device\n");
		return ret;
	}

	indio_dev->modes = INDIO_DIRECT_MODE | INDIO_BUFFER_SOFTWARE;
	indio_dev->dev.parent = &client->dev;
	indio_dev->dev.of_node = client->dev.of_node;
	if (id->driver_data == ina226) {
		indio_dev->channels = ina226_channels;
		indio_dev->num_channels = ARRAY_SIZE(ina226_channels);
		indio_dev->info = &ina226_info;
	} else {
		indio_dev->channels = ina219_channels;
		indio_dev->num_channels = ARRAY_SIZE(ina219_channels);
		indio_dev->info = &ina219_info;
	}
	indio_dev->name = id->name;
	indio_dev->setup_ops = &ina2xx_setup_ops;

	buffer = devm_iio_kfifo_allocate(&indio_dev->dev);
	if (!buffer)
		return -ENOMEM;

	iio_device_attach_buffer(indio_dev, buffer);

	return iio_device_register(indio_dev);
}