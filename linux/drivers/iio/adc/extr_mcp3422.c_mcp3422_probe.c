#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mcp3422 {int id; int /*<<< orphan*/  lock; struct i2c_client* i2c; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {void* num_channels; void* channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int MCP3422_CHANNEL_VALUE (int /*<<< orphan*/ ) ; 
 int MCP3422_CONT_SAMPLING ; 
 int /*<<< orphan*/  MCP3422_PGA_1 ; 
 int MCP3422_PGA_VALUE (int /*<<< orphan*/ ) ; 
 int MCP3422_SAMPLE_RATE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCP3422_SRATE_240 ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct mcp3422* iio_priv (struct iio_dev*) ; 
 void* mcp3421_channels ; 
 void* mcp3422_channels ; 
 int /*<<< orphan*/  mcp3422_info ; 
 int mcp3422_update_config (struct mcp3422*,int) ; 
 void* mcp3424_channels ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcp3422_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct mcp3422 *adc;
	int err;
	u8 config;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*adc));
	if (!indio_dev)
		return -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->i2c = client;
	adc->id = (u8)(id->driver_data);

	mutex_init(&adc->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->dev.of_node = client->dev.of_node;
	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &mcp3422_info;

	switch (adc->id) {
	case 1:
	case 5:
		indio_dev->channels = mcp3421_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3421_channels);
		break;
	case 2:
	case 3:
	case 6:
	case 7:
		indio_dev->channels = mcp3422_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3422_channels);
		break;
	case 4:
	case 8:
		indio_dev->channels = mcp3424_channels;
		indio_dev->num_channels = ARRAY_SIZE(mcp3424_channels);
		break;
	}

	/* meaningful default configuration */
	config = (MCP3422_CONT_SAMPLING
		| MCP3422_CHANNEL_VALUE(0)
		| MCP3422_PGA_VALUE(MCP3422_PGA_1)
		| MCP3422_SAMPLE_RATE_VALUE(MCP3422_SRATE_240));
	err = mcp3422_update_config(adc, config);
	if (err < 0)
		return err;

	err = devm_iio_device_register(&client->dev, indio_dev);
	if (err < 0)
		return err;

	i2c_set_clientdata(client, indio_dev);

	return 0;
}