#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pca9532_platform_data {int dummy; } ;
struct pca9532_data {int /*<<< orphan*/  update_lock; struct i2c_client* client; int /*<<< orphan*/ * chip_info; } ;
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (struct pca9532_platform_data*) ; 
 int PTR_ERR (struct pca9532_platform_data*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct pca9532_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct pca9532_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pca9532_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_pca9532_leds_match ; 
 int /*<<< orphan*/ * pca9532_chip_info_tbl ; 
 int pca9532_configure (struct i2c_client*,struct pca9532_data*,struct pca9532_platform_data*) ; 
 struct pca9532_platform_data* pca9532_of_populate_pdata (TYPE_1__*,struct device_node*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pca9532_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int devid;
	const struct of_device_id *of_id;
	struct pca9532_data *data = i2c_get_clientdata(client);
	struct pca9532_platform_data *pca9532_pdata =
			dev_get_platdata(&client->dev);
	struct device_node *np = client->dev.of_node;

	if (!pca9532_pdata) {
		if (np) {
			pca9532_pdata =
				pca9532_of_populate_pdata(&client->dev, np);
			if (IS_ERR(pca9532_pdata))
				return PTR_ERR(pca9532_pdata);
		} else {
			dev_err(&client->dev, "no platform data\n");
			return -EINVAL;
		}
		of_id = of_match_device(of_pca9532_leds_match,
				&client->dev);
		if (unlikely(!of_id))
			return -EINVAL;
		devid = (int)(uintptr_t) of_id->data;
	} else {
		devid = id->driver_data;
	}

	if (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->chip_info = &pca9532_chip_info_tbl[devid];

	dev_info(&client->dev, "setting platform data\n");
	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	return pca9532_configure(client, data, pca9532_pdata);
}