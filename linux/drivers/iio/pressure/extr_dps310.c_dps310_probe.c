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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dps310_data {int /*<<< orphan*/  regmap; int /*<<< orphan*/  lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DPS310_BACKGROUND ; 
 int /*<<< orphan*/  DPS310_CFG_REG ; 
 int DPS310_COEF_RDY ; 
 int /*<<< orphan*/  DPS310_MEAS_CFG ; 
 int DPS310_MEAS_CTRL_BITS ; 
 int /*<<< orphan*/  DPS310_PRS_CFG ; 
 int DPS310_PRS_EN ; 
 int DPS310_PRS_SHIFT_EN ; 
 int DPS310_TEMP_EN ; 
 int /*<<< orphan*/  DPS310_TMP_CFG ; 
 int /*<<< orphan*/  DPS310_TMP_EXT ; 
 int DPS310_TMP_SHIFT_EN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dps310_data*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dps310_channels ; 
 int dps310_get_coefs (struct dps310_data*) ; 
 int /*<<< orphan*/  dps310_info ; 
 int /*<<< orphan*/  dps310_regmap_config ; 
 int /*<<< orphan*/  dps310_reset ; 
 int dps310_temp_workaround (struct dps310_data*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct dps310_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dps310_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct dps310_data *data;
	struct iio_dev *iio;
	int rc, ready;

	iio = devm_iio_device_alloc(&client->dev,  sizeof(*data));
	if (!iio)
		return -ENOMEM;

	data = iio_priv(iio);
	data->client = client;
	mutex_init(&data->lock);

	iio->dev.parent = &client->dev;
	iio->name = id->name;
	iio->channels = dps310_channels;
	iio->num_channels = ARRAY_SIZE(dps310_channels);
	iio->info = &dps310_info;
	iio->modes = INDIO_DIRECT_MODE;

	data->regmap = devm_regmap_init_i2c(client, &dps310_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	/* Register to run the device reset when the device is removed */
	rc = devm_add_action_or_reset(&client->dev, dps310_reset, data);
	if (rc)
		return rc;

	/*
	 * Set up pressure sensor in single sample, one measurement per second
	 * mode
	 */
	rc = regmap_write(data->regmap, DPS310_PRS_CFG, 0);

	/*
	 * Set up external (MEMS) temperature sensor in single sample, one
	 * measurement per second mode
	 */
	rc = regmap_write(data->regmap, DPS310_TMP_CFG, DPS310_TMP_EXT);
	if (rc < 0)
		return rc;

	/* Temp and pressure shifts are disabled when PRC <= 8 */
	rc = regmap_write_bits(data->regmap, DPS310_CFG_REG,
			       DPS310_PRS_SHIFT_EN | DPS310_TMP_SHIFT_EN, 0);
	if (rc < 0)
		return rc;

	/* MEAS_CFG doesn't update correctly unless first written with 0 */
	rc = regmap_write_bits(data->regmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTRL_BITS, 0);
	if (rc < 0)
		return rc;

	/* Turn on temperature and pressure measurement in the background */
	rc = regmap_write_bits(data->regmap, DPS310_MEAS_CFG,
			       DPS310_MEAS_CTRL_BITS, DPS310_PRS_EN |
			       DPS310_TEMP_EN | DPS310_BACKGROUND);
	if (rc < 0)
		return rc;

	/*
	 * Calibration coefficients required for reporting temperature.
	 * They are available 40ms after the device has started
	 */
	rc = regmap_read_poll_timeout(data->regmap, DPS310_MEAS_CFG, ready,
				      ready & DPS310_COEF_RDY, 10000, 40000);
	if (rc < 0)
		return rc;

	rc = dps310_get_coefs(data);
	if (rc < 0)
		return rc;

	rc = dps310_temp_workaround(data);
	if (rc < 0)
		return rc;

	rc = devm_iio_device_register(&client->dev, iio);
	if (rc)
		return rc;

	i2c_set_clientdata(client, iio);

	return 0;
}