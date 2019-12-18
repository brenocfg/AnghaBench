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
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;
struct dac5571_spec {int num_channels; } ;
struct dac5571_data {int (* dac5571_cmd ) (struct dac5571_data*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  vref; int /*<<< orphan*/  dac5571_pwrdwn; int /*<<< orphan*/  lock; struct dac5571_spec const* spec; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac5571_channels ; 
 int dac5571_cmd_quad (struct dac5571_data*,int,int /*<<< orphan*/ ) ; 
 int dac5571_cmd_single (struct dac5571_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac5571_info ; 
 int /*<<< orphan*/  dac5571_pwrdwn_quad ; 
 int /*<<< orphan*/  dac5571_pwrdwn_single ; 
 struct dac5571_spec* dac5571_spec ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct dac5571_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int stub1 (struct dac5571_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dac5571_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	const struct dac5571_spec *spec;
	struct dac5571_data *data;
	struct iio_dev *indio_dev;
	int ret, i;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = client->dev.of_node;
	indio_dev->info = &dac5571_info;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = dac5571_channels;

	spec = &dac5571_spec[id->driver_data];
	indio_dev->num_channels = spec->num_channels;
	data->spec = spec;

	data->vref = devm_regulator_get(dev, "vref");
	if (IS_ERR(data->vref))
		return PTR_ERR(data->vref);

	ret = regulator_enable(data->vref);
	if (ret < 0)
		return ret;

	mutex_init(&data->lock);

	switch (spec->num_channels) {
	case 1:
		data->dac5571_cmd = dac5571_cmd_single;
		data->dac5571_pwrdwn = dac5571_pwrdwn_single;
		break;
	case 4:
		data->dac5571_cmd = dac5571_cmd_quad;
		data->dac5571_pwrdwn = dac5571_pwrdwn_quad;
		break;
	default:
		goto err;
	}

	for (i = 0; i < spec->num_channels; i++) {
		ret = data->dac5571_cmd(data, i, 0);
		if (ret) {
			dev_err(dev, "failed to initialize channel %d to 0\n", i);
			goto err;
		}
	}

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err;

	return 0;

 err:
	regulator_disable(data->vref);
	return ret;
}