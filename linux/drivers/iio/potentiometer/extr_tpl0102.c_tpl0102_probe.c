#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tpl0102_data {TYPE_2__* cfg; int /*<<< orphan*/  regmap; } ;
struct TYPE_3__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {size_t driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  wipers; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct tpl0102_data* iio_priv (struct iio_dev*) ; 
 TYPE_2__* tpl0102_cfg ; 
 int /*<<< orphan*/  tpl0102_channels ; 
 int /*<<< orphan*/  tpl0102_info ; 
 int /*<<< orphan*/  tpl0102_regmap_config ; 

__attribute__((used)) static int tpl0102_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct tpl0102_data *data;
	struct iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	data->cfg = &tpl0102_cfg[id->driver_data];
	data->regmap = devm_regmap_init_i2c(client, &tpl0102_regmap_config);
	if (IS_ERR(data->regmap)) {
		dev_err(dev, "regmap initialization failed\n");
		return PTR_ERR(data->regmap);
	}

	indio_dev->dev.parent = dev;
	indio_dev->info = &tpl0102_info;
	indio_dev->channels = tpl0102_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = client->name;

	return devm_iio_device_register(dev, indio_dev);
}