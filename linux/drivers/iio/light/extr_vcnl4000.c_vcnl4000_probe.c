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
struct vcnl4000_data {size_t id; int /*<<< orphan*/  rev; TYPE_2__* chip_spec; struct i2c_client* client; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {size_t driver_data; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* init ) (struct vcnl4000_data*) ;int /*<<< orphan*/  prod; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  VCNL4000_DRV_NAME ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct vcnl4000_data* iio_priv (struct iio_dev*) ; 
 int stub1 (struct vcnl4000_data*) ; 
 int /*<<< orphan*/  vcnl4000_channels ; 
 TYPE_2__* vcnl4000_chip_spec_cfg ; 
 int /*<<< orphan*/  vcnl4000_info ; 

__attribute__((used)) static int vcnl4000_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct vcnl4000_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->id = id->driver_data;
	data->chip_spec = &vcnl4000_chip_spec_cfg[data->id];

	ret = data->chip_spec->init(data);
	if (ret < 0)
		return ret;

	dev_dbg(&client->dev, "%s Ambient light/proximity sensor, Rev: %02x\n",
		data->chip_spec->prod, data->rev);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &vcnl4000_info;
	indio_dev->channels = vcnl4000_channels;
	indio_dev->num_channels = ARRAY_SIZE(vcnl4000_channels);
	indio_dev->name = VCNL4000_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	return devm_iio_device_register(&client->dev, indio_dev);
}