#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct drv260x_data {int mode; int library; TYPE_1__* input_dev; int /*<<< orphan*/  regmap; struct i2c_client* client; int /*<<< orphan*/  work; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  regulator; void* overdrive_voltage; void* rated_voltage; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  close; } ;

/* Variables and functions */
 void* DRV260X_DEF_OD_CLAMP_VOLT ; 
 void* DRV260X_DEF_RATED_VOLT ; 
 int DRV260X_ERM_LIB_F ; 
 int DRV260X_ERM_MODE ; 
 int DRV260X_LIB_EMPTY ; 
 int DRV260X_LIB_LRA ; 
 int DRV260X_LRA_MODE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_FF ; 
 int /*<<< orphan*/  FF_RUMBLE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_input_allocate_device (struct device*) ; 
 struct drv260x_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 void* drv260x_calculate_voltage (int) ; 
 int /*<<< orphan*/  drv260x_close ; 
 int /*<<< orphan*/  drv260x_haptics_play ; 
 int drv260x_init (struct drv260x_data*) ; 
 int /*<<< orphan*/  drv260x_regmap_config ; 
 int /*<<< orphan*/  drv260x_worker ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct drv260x_data*) ; 
 int input_ff_create_memless (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int input_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  input_set_capability (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_1__*,struct drv260x_data*) ; 

__attribute__((used)) static int drv260x_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct drv260x_data *haptics;
	u32 voltage;
	int error;

	haptics = devm_kzalloc(dev, sizeof(*haptics), GFP_KERNEL);
	if (!haptics)
		return -ENOMEM;

	error = device_property_read_u32(dev, "mode", &haptics->mode);
	if (error) {
		dev_err(dev, "Can't fetch 'mode' property: %d\n", error);
		return error;
	}

	if (haptics->mode < DRV260X_LRA_MODE ||
	    haptics->mode > DRV260X_ERM_MODE) {
		dev_err(dev, "Vibrator mode is invalid: %i\n", haptics->mode);
		return -EINVAL;
	}

	error = device_property_read_u32(dev, "library-sel", &haptics->library);
	if (error) {
		dev_err(dev, "Can't fetch 'library-sel' property: %d\n", error);
		return error;
	}

	if (haptics->library < DRV260X_LIB_EMPTY ||
	    haptics->library > DRV260X_ERM_LIB_F) {
		dev_err(dev,
			"Library value is invalid: %i\n", haptics->library);
		return -EINVAL;
	}

	if (haptics->mode == DRV260X_LRA_MODE &&
	    haptics->library != DRV260X_LIB_EMPTY &&
	    haptics->library != DRV260X_LIB_LRA) {
		dev_err(dev, "LRA Mode with ERM Library mismatch\n");
		return -EINVAL;
	}

	if (haptics->mode == DRV260X_ERM_MODE &&
	    (haptics->library == DRV260X_LIB_EMPTY ||
	     haptics->library == DRV260X_LIB_LRA)) {
		dev_err(dev, "ERM Mode with LRA Library mismatch\n");
		return -EINVAL;
	}

	error = device_property_read_u32(dev, "vib-rated-mv", &voltage);
	haptics->rated_voltage = error ? DRV260X_DEF_RATED_VOLT :
					 drv260x_calculate_voltage(voltage);

	error = device_property_read_u32(dev, "vib-overdrive-mv", &voltage);
	haptics->overdrive_voltage = error ? DRV260X_DEF_OD_CLAMP_VOLT :
					     drv260x_calculate_voltage(voltage);

	haptics->regulator = devm_regulator_get(dev, "vbat");
	if (IS_ERR(haptics->regulator)) {
		error = PTR_ERR(haptics->regulator);
		dev_err(dev, "unable to get regulator, error: %d\n", error);
		return error;
	}

	haptics->enable_gpio = devm_gpiod_get_optional(dev, "enable",
						       GPIOD_OUT_HIGH);
	if (IS_ERR(haptics->enable_gpio))
		return PTR_ERR(haptics->enable_gpio);

	haptics->input_dev = devm_input_allocate_device(dev);
	if (!haptics->input_dev) {
		dev_err(dev, "Failed to allocate input device\n");
		return -ENOMEM;
	}

	haptics->input_dev->name = "drv260x:haptics";
	haptics->input_dev->close = drv260x_close;
	input_set_drvdata(haptics->input_dev, haptics);
	input_set_capability(haptics->input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(haptics->input_dev, NULL,
					drv260x_haptics_play);
	if (error) {
		dev_err(dev, "input_ff_create() failed: %d\n", error);
		return error;
	}

	INIT_WORK(&haptics->work, drv260x_worker);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client, &drv260x_regmap_config);
	if (IS_ERR(haptics->regmap)) {
		error = PTR_ERR(haptics->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		return error;
	}

	error = drv260x_init(haptics);
	if (error) {
		dev_err(dev, "Device init failed: %d\n", error);
		return error;
	}

	error = input_register_device(haptics->input_dev);
	if (error) {
		dev_err(dev, "couldn't register input device: %d\n", error);
		return error;
	}

	return 0;
}