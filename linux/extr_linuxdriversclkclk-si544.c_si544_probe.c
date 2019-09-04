#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_9__ {TYPE_1__* of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_10__ {struct clk_init_data* init; } ;
struct clk_si544 {TYPE_3__ hw; int /*<<< orphan*/  regmap; int /*<<< orphan*/  speed_grade; struct i2c_client* i2c_client; } ;
struct clk_init_data {int /*<<< orphan*/  name; scalar_t__ num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI544_REG_PAGE_SELECT ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int devm_clk_hw_register (TYPE_2__*,TYPE_3__*) ; 
 struct clk_si544* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct clk_si544*) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 scalar_t__ of_property_read_string (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si544_clk_ops ; 
 int /*<<< orphan*/  si544_regmap_config ; 

__attribute__((used)) static int si544_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	struct clk_si544 *data;
	struct clk_init_data init;
	int err;

	data = devm_kzalloc(&client->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	init.ops = &si544_clk_ops;
	init.flags = 0;
	init.num_parents = 0;
	data->hw.init = &init;
	data->i2c_client = client;
	data->speed_grade = id->driver_data;

	if (of_property_read_string(client->dev.of_node, "clock-output-names",
			&init.name))
		init.name = client->dev.of_node->name;

	data->regmap = devm_regmap_init_i2c(client, &si544_regmap_config);
	if (IS_ERR(data->regmap))
		return PTR_ERR(data->regmap);

	i2c_set_clientdata(client, data);

	/* Select page 0, just to be sure, there appear to be no more */
	err = regmap_write(data->regmap, SI544_REG_PAGE_SELECT, 0);
	if (err < 0)
		return err;

	err = devm_clk_hw_register(&client->dev, &data->hw);
	if (err) {
		dev_err(&client->dev, "clock registration failed\n");
		return err;
	}
	err = devm_of_clk_add_hw_provider(&client->dev, of_clk_hw_simple_get,
					  &data->hw);
	if (err) {
		dev_err(&client->dev, "unable to add clk provider\n");
		return err;
	}

	return 0;
}