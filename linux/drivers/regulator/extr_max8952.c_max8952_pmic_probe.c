#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct regulator_config {struct regulator_dev* ena_gpiod; scalar_t__ of_node; struct max8952_data* driver_data; TYPE_2__* init_data; TYPE_3__* dev; } ;
struct max8952_platform_data {int default_mode; int* dvs_mode; int sync_freq; int ramp_speed; TYPE_2__* reg_data; } ;
struct max8952_data {int vid0; int vid1; struct regulator_dev* vid1_gpiod; struct regulator_dev* vid0_gpiod; struct max8952_platform_data* pdata; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_3__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
typedef  struct regulator_dev gpio_desc ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;
struct TYPE_11__ {scalar_t__ boot_on; } ;
struct TYPE_12__ {TYPE_1__ constraints; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  MAX8952_REG_CONTROL ; 
 int /*<<< orphan*/  MAX8952_REG_MODE0 ; 
 int /*<<< orphan*/  MAX8952_REG_MODE1 ; 
 int /*<<< orphan*/  MAX8952_REG_MODE2 ; 
 int /*<<< orphan*/  MAX8952_REG_MODE3 ; 
 int /*<<< orphan*/  MAX8952_REG_RAMP ; 
 int /*<<< orphan*/  MAX8952_REG_SYNC ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct max8952_platform_data* dev_get_platdata (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 void* devm_gpiod_get_index_optional (TYPE_3__*,char*,int,int) ; 
 struct max8952_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_3__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 struct regulator_dev* gpiod_get_optional (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value (struct regulator_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max8952_data*) ; 
 struct max8952_platform_data* max8952_parse_dt (TYPE_3__*) ; 
 int max8952_read_reg (struct max8952_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max8952_write_reg (struct max8952_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator ; 

__attribute__((used)) static int max8952_pmic_probe(struct i2c_client *client,
		const struct i2c_device_id *i2c_id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct max8952_platform_data *pdata = dev_get_platdata(&client->dev);
	struct regulator_config config = { };
	struct max8952_data *max8952;
	struct regulator_dev *rdev;
	struct gpio_desc *gpiod;
	enum gpiod_flags gflags;

	int ret = 0;

	if (client->dev.of_node)
		pdata = max8952_parse_dt(&client->dev);

	if (!pdata) {
		dev_err(&client->dev, "Require the platform data\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		return -EIO;

	max8952 = devm_kzalloc(&client->dev, sizeof(struct max8952_data),
			       GFP_KERNEL);
	if (!max8952)
		return -ENOMEM;

	max8952->client = client;
	max8952->pdata = pdata;

	config.dev = &client->dev;
	config.init_data = pdata->reg_data;
	config.driver_data = max8952;
	config.of_node = client->dev.of_node;

	if (pdata->reg_data->constraints.boot_on)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_LOW;
	gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;
	/*
	 * Do not use devm* here: the regulator core takes over the
	 * lifecycle management of the GPIO descriptor.
	 */
	gpiod = gpiod_get_optional(&client->dev,
				   "max8952,en",
				   gflags);
	if (IS_ERR(gpiod))
		return PTR_ERR(gpiod);
	if (gpiod)
		config.ena_gpiod = gpiod;

	rdev = devm_regulator_register(&client->dev, &regulator, &config);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(&client->dev, "regulator init failed (%d)\n", ret);
		return ret;
	}

	max8952->vid0 = pdata->default_mode & 0x1;
	max8952->vid1 = (pdata->default_mode >> 1) & 0x1;

	/* Fetch vid0 and vid1 GPIOs if available */
	gflags = max8952->vid0 ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	max8952->vid0_gpiod = devm_gpiod_get_index_optional(&client->dev,
							    "max8952,vid",
							    0, gflags);
	if (IS_ERR(max8952->vid0_gpiod))
		return PTR_ERR(max8952->vid0_gpiod);
	gflags = max8952->vid1 ? GPIOD_OUT_HIGH : GPIOD_OUT_LOW;
	max8952->vid1_gpiod = devm_gpiod_get_index_optional(&client->dev,
							    "max8952,vid",
							    1, gflags);
	if (IS_ERR(max8952->vid1_gpiod))
		return PTR_ERR(max8952->vid1_gpiod);

	/* If either VID GPIO is missing just disable this */
	if (!max8952->vid0_gpiod || !max8952->vid1_gpiod) {
		dev_warn(&client->dev, "VID0/1 gpio invalid: "
			 "DVS not available.\n");
		max8952->vid0 = 0;
		max8952->vid1 = 0;
		/* Make sure if we have any descriptors they get set to low */
		if (max8952->vid0_gpiod)
			gpiod_set_value(max8952->vid0_gpiod, 0);
		if (max8952->vid1_gpiod)
			gpiod_set_value(max8952->vid1_gpiod, 0);

		/* Disable Pulldown of EN only */
		max8952_write_reg(max8952, MAX8952_REG_CONTROL, 0x60);

		dev_err(&client->dev, "DVS modes disabled because VID0 and VID1"
				" do not have proper controls.\n");
	} else {
		/*
		 * Disable Pulldown on EN, VID0, VID1 to reduce
		 * leakage current of MAX8952 assuming that MAX8952
		 * is turned on (EN==1). Note that without having VID0/1
		 * properly connected, turning pulldown off can be
		 * problematic. Thus, turn this off only when they are
		 * controllable by GPIO.
		 */
		max8952_write_reg(max8952, MAX8952_REG_CONTROL, 0x0);
	}

	max8952_write_reg(max8952, MAX8952_REG_MODE0,
			(max8952_read_reg(max8952,
					  MAX8952_REG_MODE0) & 0xC0) |
			(pdata->dvs_mode[0] & 0x3F));
	max8952_write_reg(max8952, MAX8952_REG_MODE1,
			(max8952_read_reg(max8952,
					  MAX8952_REG_MODE1) & 0xC0) |
			(pdata->dvs_mode[1] & 0x3F));
	max8952_write_reg(max8952, MAX8952_REG_MODE2,
			(max8952_read_reg(max8952,
					  MAX8952_REG_MODE2) & 0xC0) |
			(pdata->dvs_mode[2] & 0x3F));
	max8952_write_reg(max8952, MAX8952_REG_MODE3,
			(max8952_read_reg(max8952,
					  MAX8952_REG_MODE3) & 0xC0) |
			(pdata->dvs_mode[3] & 0x3F));

	max8952_write_reg(max8952, MAX8952_REG_SYNC,
			(max8952_read_reg(max8952, MAX8952_REG_SYNC) & 0x3F) |
			((pdata->sync_freq & 0x3) << 6));
	max8952_write_reg(max8952, MAX8952_REG_RAMP,
			(max8952_read_reg(max8952, MAX8952_REG_RAMP) & 0x1F) |
			((pdata->ramp_speed & 0x7) << 5));

	i2c_set_clientdata(client, max8952);

	return 0;
}