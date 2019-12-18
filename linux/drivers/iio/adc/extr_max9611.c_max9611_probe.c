#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {int /*<<< orphan*/  data; } ;
struct max9611_dev {unsigned int shunt_resistor_uohm; int /*<<< orphan*/  lock; struct i2c_client* i2c_client; TYPE_2__* dev; } ;
struct TYPE_6__ {struct device_node* of_node; TYPE_2__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,char const* const,struct device_node const*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct max9611_dev* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  indio_info ; 
 int /*<<< orphan*/  max9611_channels ; 
 int max9611_init (struct max9611_dev*) ; 
 int /*<<< orphan*/  max9611_of_table ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int of_property_read_u32 (struct device_node const*,char const* const,unsigned int*) ; 

__attribute__((used)) static int max9611_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	const char * const shunt_res_prop = "shunt-resistor-micro-ohms";
	const struct device_node *of_node = client->dev.of_node;
	const struct of_device_id *of_id =
		of_match_device(max9611_of_table, &client->dev);
	struct max9611_dev *max9611;
	struct iio_dev *indio_dev;
	unsigned int of_shunt;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*max9611));
	if (!indio_dev)
		return -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	max9611			= iio_priv(indio_dev);
	max9611->dev		= &client->dev;
	max9611->i2c_client	= client;
	mutex_init(&max9611->lock);

	ret = of_property_read_u32(of_node, shunt_res_prop, &of_shunt);
	if (ret) {
		dev_err(&client->dev,
			"Missing %s property for %pOF node\n",
			shunt_res_prop, of_node);
		return ret;
	}
	max9611->shunt_resistor_uohm = of_shunt;

	ret = max9611_init(max9611);
	if (ret)
		return ret;

	indio_dev->dev.parent	= &client->dev;
	indio_dev->dev.of_node	= client->dev.of_node;
	indio_dev->name		= of_id->data;
	indio_dev->modes	= INDIO_DIRECT_MODE;
	indio_dev->info		= &indio_info;
	indio_dev->channels	= max9611_channels;
	indio_dev->num_channels	= ARRAY_SIZE(max9611_channels);

	return devm_iio_device_register(&client->dev, indio_dev);
}