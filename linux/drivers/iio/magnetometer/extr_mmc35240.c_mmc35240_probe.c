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
struct mmc35240_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  res; struct regmap* regmap; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  MMC35240_16_BITS_SLOW ; 
 int /*<<< orphan*/  MMC35240_DRV_NAME ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct mmc35240_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mmc35240_channels ; 
 int /*<<< orphan*/  mmc35240_info ; 
 int mmc35240_init (struct mmc35240_data*) ; 
 int /*<<< orphan*/  mmc35240_regmap_config ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc35240_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct mmc35240_data *data;
	struct iio_dev *indio_dev;
	struct regmap *regmap;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &mmc35240_regmap_config);
	if (IS_ERR(regmap)) {
		dev_err(&client->dev, "regmap initialization failed\n");
		return PTR_ERR(regmap);
	}

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;
	data->res = MMC35240_16_BITS_SLOW;

	mutex_init(&data->mutex);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &mmc35240_info;
	indio_dev->name = MMC35240_DRV_NAME;
	indio_dev->channels = mmc35240_channels;
	indio_dev->num_channels = ARRAY_SIZE(mmc35240_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = mmc35240_init(data);
	if (ret < 0) {
		dev_err(&client->dev, "mmc35240 chip init failed\n");
		return ret;
	}
	return devm_iio_device_register(&client->dev, indio_dev);
}