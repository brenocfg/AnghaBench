#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct max732x_platform_data {int (* setup ) (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; int /*<<< orphan*/  gpio_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; TYPE_1__* parent; } ;
struct max732x_chip {TYPE_5__ gpio_chip; int /*<<< orphan*/ * reg_out; int /*<<< orphan*/  lock; struct i2c_client* client_dummy; struct i2c_client* client_group_a; struct i2c_client* client_group_b; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct i2c_client {int addr; TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct i2c_client*) ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct max732x_platform_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int devm_gpiochip_add_data (TYPE_1__*,TYPE_5__*,struct max732x_chip*) ; 
 struct i2c_client* devm_i2c_new_dummy_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct max732x_chip* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max732x_chip*) ; 
 int /*<<< orphan*/  is_group_a (struct max732x_chip*,int) ; 
 int max732x_irq_setup (struct max732x_chip*,struct i2c_device_id const*) ; 
 int max732x_readb (struct max732x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max732x_setup_gpio (struct max732x_chip*,struct i2c_device_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct max732x_platform_data* of_gpio_max732x (TYPE_1__*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max732x_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
	struct max732x_platform_data *pdata;
	struct device_node *node;
	struct max732x_chip *chip;
	struct i2c_client *c;
	uint16_t addr_a, addr_b;
	int ret, nr_port;

	pdata = dev_get_platdata(&client->dev);
	node = client->dev.of_node;

	if (!pdata && node)
		pdata = of_gpio_max732x(&client->dev);

	if (!pdata) {
		dev_dbg(&client->dev, "no platform data\n");
		return -EINVAL;
	}

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;
	chip->client = client;

	nr_port = max732x_setup_gpio(chip, id, pdata->gpio_base);
	chip->gpio_chip.parent = &client->dev;

	addr_a = (client->addr & 0x0f) | 0x60;
	addr_b = (client->addr & 0x0f) | 0x50;

	switch (client->addr & 0x70) {
	case 0x60:
		chip->client_group_a = client;
		if (nr_port > 8) {
			c = devm_i2c_new_dummy_device(&client->dev,
						      client->adapter, addr_b);
			if (IS_ERR(c)) {
				dev_err(&client->dev,
					"Failed to allocate I2C device\n");
				return PTR_ERR(c);
			}
			chip->client_group_b = chip->client_dummy = c;
		}
		break;
	case 0x50:
		chip->client_group_b = client;
		if (nr_port > 8) {
			c = devm_i2c_new_dummy_device(&client->dev,
						      client->adapter, addr_a);
			if (IS_ERR(c)) {
				dev_err(&client->dev,
					"Failed to allocate I2C device\n");
				return PTR_ERR(c);
			}
			chip->client_group_a = chip->client_dummy = c;
		}
		break;
	default:
		dev_err(&client->dev, "invalid I2C address specified %02x\n",
				client->addr);
		return -EINVAL;
	}

	if (nr_port > 8 && !chip->client_dummy) {
		dev_err(&client->dev,
			"Failed to allocate second group I2C device\n");
		return -ENODEV;
	}

	mutex_init(&chip->lock);

	ret = max732x_readb(chip, is_group_a(chip, 0), &chip->reg_out[0]);
	if (ret)
		return ret;
	if (nr_port > 8) {
		ret = max732x_readb(chip, is_group_a(chip, 8), &chip->reg_out[1]);
		if (ret)
			return ret;
	}

	ret = devm_gpiochip_add_data(&client->dev, &chip->gpio_chip, chip);
	if (ret)
		return ret;

	ret = max732x_irq_setup(chip, id);
	if (ret)
		return ret;

	if (pdata && pdata->setup) {
		ret = pdata->setup(client, chip->gpio_chip.base,
				chip->gpio_chip.ngpio, pdata->context);
		if (ret < 0)
			dev_warn(&client->dev, "setup failed, %d\n", ret);
	}

	i2c_set_clientdata(client, chip);
	return 0;
}