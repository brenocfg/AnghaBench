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
struct regmap {int dummy; } ;
struct noa1305_priv {struct regmap* regmap; struct i2c_client* client; struct regmap* vin_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 unsigned int NOA1305_DEVICE_ID ; 
 int /*<<< orphan*/  NOA1305_DRIVER_NAME ; 
 int /*<<< orphan*/  NOA1305_INTEGR_TIME_800MS ; 
 int /*<<< orphan*/  NOA1305_POWER_CONTROL_ON ; 
 int /*<<< orphan*/  NOA1305_REG_DEVICE_ID_LSB ; 
 int /*<<< orphan*/  NOA1305_REG_INTEGRATION_TIME ; 
 int /*<<< orphan*/  NOA1305_REG_POWER_CONTROL ; 
 int /*<<< orphan*/  NOA1305_REG_RESET ; 
 int /*<<< orphan*/  NOA1305_RESET_RESET ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct noa1305_priv*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 struct regmap* devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct noa1305_priv* iio_priv (struct iio_dev*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noa1305_channels ; 
 int /*<<< orphan*/  noa1305_info ; 
 int /*<<< orphan*/  noa1305_reg_remove ; 
 int /*<<< orphan*/  noa1305_regmap_config ; 
 int regmap_bulk_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (struct regmap*) ; 

__attribute__((used)) static int noa1305_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct noa1305_priv *priv;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	__le16 data;
	unsigned int dev_id;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &noa1305_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "Regmap initialization failed.\n");
		return PTR_ERR(regmap);
	}

	priv = iio_priv(indio_dev);

	priv->vin_reg = devm_regulator_get(&client->dev, "vin");
	if (IS_ERR(priv->vin_reg)) {
		dev_err(&client->dev, "get regulator vin failed\n");
		return PTR_ERR(priv->vin_reg);
	}

	ret = regulator_enable(priv->vin_reg);
	if (ret) {
		dev_err(&client->dev, "enable regulator vin failed\n");
		return ret;
	}

	ret = devm_add_action_or_reset(&client->dev, noa1305_reg_remove, priv);
	if (ret) {
		dev_err(&client->dev, "addition of devm action failed\n");
		return ret;
	}

	i2c_set_clientdata(client, indio_dev);
	priv->client = client;
	priv->regmap = regmap;

	ret = regmap_bulk_read(regmap, NOA1305_REG_DEVICE_ID_LSB, &data, 2);
	if (ret < 0) {
		dev_err(&client->dev, "ID reading failed: %d\n", ret);
		return ret;
	}

	dev_id = le16_to_cpu(data);
	if (dev_id != NOA1305_DEVICE_ID) {
		dev_err(&client->dev, "Unknown device ID: 0x%x\n", dev_id);
		return -ENODEV;
	}

	ret = regmap_write(regmap, NOA1305_REG_POWER_CONTROL,
			   NOA1305_POWER_CONTROL_ON);
	if (ret < 0) {
		dev_err(&client->dev, "Enabling power control failed\n");
		return ret;
	}

	ret = regmap_write(regmap, NOA1305_REG_RESET, NOA1305_RESET_RESET);
	if (ret < 0) {
		dev_err(&client->dev, "Device reset failed\n");
		return ret;
	}

	ret = regmap_write(regmap, NOA1305_REG_INTEGRATION_TIME,
			   NOA1305_INTEGR_TIME_800MS);
	if (ret < 0) {
		dev_err(&client->dev, "Setting integration time failed\n");
		return ret;
	}

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &noa1305_info;
	indio_dev->channels = noa1305_channels;
	indio_dev->num_channels = ARRAY_SIZE(noa1305_channels);
	indio_dev->name = NOA1305_DRIVER_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = devm_iio_device_register(&client->dev, indio_dev);
	if (ret)
		dev_err(&client->dev, "registering device failed\n");

	return ret;
}