#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mcp4531_data {TYPE_2__* cfg; struct i2c_client* client; } ;
struct TYPE_5__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; struct device dev; } ;
struct TYPE_7__ {size_t driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  wipers; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* i2c_match_id (int /*<<< orphan*/ ,struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct mcp4531_data* iio_priv (struct iio_dev*) ; 
 TYPE_2__* mcp4531_cfg ; 
 int /*<<< orphan*/  mcp4531_channels ; 
 int /*<<< orphan*/  mcp4531_id ; 
 int /*<<< orphan*/  mcp4531_info ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int mcp4531_probe(struct i2c_client *client)
{
	struct device *dev = &client->dev;
	struct mcp4531_data *data;
	struct iio_dev *indio_dev;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_err(dev, "SMBUS Word Data not supported\n");
		return -EOPNOTSUPP;
	}

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;
	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	data->cfg = of_device_get_match_data(dev);
	if (!data->cfg)
		data->cfg = &mcp4531_cfg[i2c_match_id(mcp4531_id, client)->driver_data];

	indio_dev->dev.parent = dev;
	indio_dev->info = &mcp4531_info;
	indio_dev->channels = mcp4531_channels;
	indio_dev->num_channels = data->cfg->wipers;
	indio_dev->name = client->name;

	return devm_iio_device_register(dev, indio_dev);
}