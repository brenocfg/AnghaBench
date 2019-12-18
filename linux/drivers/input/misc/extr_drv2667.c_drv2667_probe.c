#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_6__ dev; } ;
struct drv2667_data {TYPE_2__* input_dev; int /*<<< orphan*/  regmap; struct i2c_client* client; int /*<<< orphan*/  work; int /*<<< orphan*/  regulator; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct TYPE_12__ {char* name; int /*<<< orphan*/  close; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 TYPE_2__* devm_input_allocate_device (TYPE_6__*) ; 
 struct drv2667_data* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  drv2667_close ; 
 int /*<<< orphan*/  drv2667_haptics_play ; 
 int drv2667_init (struct drv2667_data*) ; 
 int /*<<< orphan*/  drv2667_regmap_config ; 
 int /*<<< orphan*/  drv2667_worker ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct drv2667_data*) ; 
 int input_ff_create_memless (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct drv2667_data*) ; 

__attribute__((used)) static int drv2667_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct drv2667_data *haptics;
	int error;

	haptics = devm_kzalloc(&client->dev, sizeof(*haptics), GFP_KERNEL);
	if (!haptics)
		return -ENOMEM;

	haptics->regulator = devm_regulator_get(&client->dev, "vbat");
	if (IS_ERR(haptics->regulator)) {
		error = PTR_ERR(haptics->regulator);
		dev_err(&client->dev,
			"unable to get regulator, error: %d\n", error);
		return error;
	}

	haptics->input_dev = devm_input_allocate_device(&client->dev);
	if (!haptics->input_dev) {
		dev_err(&client->dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	haptics->input_dev->name = "drv2667:haptics";
	haptics->input_dev->dev.parent = client->dev.parent;
	haptics->input_dev->close = drv2667_close;
	input_set_drvdata(haptics->input_dev, haptics);
	input_set_capability(haptics->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptics->input_dev, NULL,
					drv2667_haptics_play);
	if (error) {
		dev_err(&client->dev, "input_ff_create() failed: %d\n",
			error);
		return error;
	}

	INIT_WORK(&haptics->work, drv2667_worker);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client, &drv2667_regmap_config);
	if (IS_ERR(haptics->regmap)) {
		error = PTR_ERR(haptics->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			error);
		return error;
	}

	error = drv2667_init(haptics);
	if (error) {
		dev_err(&client->dev, "Device init failed: %d\n", error);
		return error;
	}

	error = input_register_device(haptics->input_dev);
	if (error) {
		dev_err(&client->dev, "couldn't register input device: %d\n",
			error);
		return error;
	}

	return 0;
}