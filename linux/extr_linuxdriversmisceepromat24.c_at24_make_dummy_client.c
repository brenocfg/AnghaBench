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
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {unsigned int addr; int /*<<< orphan*/  adapter; struct device dev; } ;
struct at24_data {TYPE_1__* client; } ;
struct TYPE_2__ {struct regmap* regmap; struct i2c_client* client; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned short) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 
 struct i2c_client* i2c_new_dummy (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 

__attribute__((used)) static int at24_make_dummy_client(struct at24_data *at24, unsigned int index,
				  struct regmap_config *regmap_config)
{
	struct i2c_client *base_client, *dummy_client;
	unsigned short int addr;
	struct regmap *regmap;
	struct device *dev;

	base_client = at24->client[0].client;
	dev = &base_client->dev;
	addr = base_client->addr + index;

	dummy_client = i2c_new_dummy(base_client->adapter,
				     base_client->addr + index);
	if (!dummy_client) {
		dev_err(dev, "address 0x%02x unavailable\n", addr);
		return -EADDRINUSE;
	}

	regmap = devm_regmap_init_i2c(dummy_client, regmap_config);
	if (IS_ERR(regmap)) {
		i2c_unregister_device(dummy_client);
		return PTR_ERR(regmap);
	}

	at24->client[index].client = dummy_client;
	at24->client[index].regmap = regmap;

	return 0;
}