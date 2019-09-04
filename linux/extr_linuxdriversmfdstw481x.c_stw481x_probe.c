#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stw481x {int /*<<< orphan*/  map; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int pdata_size; struct stw481x* platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct stw481x* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct stw481x*) ; 
 TYPE_1__* stw481x_cells ; 
 int /*<<< orphan*/  stw481x_regmap_config ; 
 int stw481x_startup (struct stw481x*) ; 

__attribute__((used)) static int stw481x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct stw481x			*stw481x;
	int ret;
	int i;

	stw481x = devm_kzalloc(&client->dev, sizeof(*stw481x), GFP_KERNEL);
	if (!stw481x)
		return -ENOMEM;

	i2c_set_clientdata(client, stw481x);
	stw481x->client = client;
	stw481x->map = devm_regmap_init_i2c(client, &stw481x_regmap_config);
	if (IS_ERR(stw481x->map)) {
		ret = PTR_ERR(stw481x->map);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = stw481x_startup(stw481x);
	if (ret) {
		dev_err(&client->dev, "chip initialization failed\n");
		return ret;
	}

	/* Set up and register the platform devices. */
	for (i = 0; i < ARRAY_SIZE(stw481x_cells); i++) {
		/* One state holder for all drivers, this is simple */
		stw481x_cells[i].platform_data = stw481x;
		stw481x_cells[i].pdata_size = sizeof(*stw481x);
	}

	ret = devm_mfd_add_devices(&client->dev, 0, stw481x_cells,
				   ARRAY_SIZE(stw481x_cells), NULL, 0, NULL);
	if (ret)
		return ret;

	dev_info(&client->dev, "initialized STw481x device\n");

	return ret;
}