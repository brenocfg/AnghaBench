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
struct of_device_id {struct lochnagar_config* data; } ;
struct lochnagar_config {unsigned int id; int /*<<< orphan*/  npatch; int /*<<< orphan*/  patch; int /*<<< orphan*/  name; TYPE_1__* regmap; int /*<<< orphan*/  type; } ;
struct lochnagar {struct gpio_desc* regmap; int /*<<< orphan*/  type; int /*<<< orphan*/  analogue_config_lock; struct device* dev; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct gpio_desc {int dummy; } ;
struct TYPE_2__ {unsigned int val_bits; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 unsigned int LOCHNAGAR_DEVICE_ID_MASK ; 
 int /*<<< orphan*/  LOCHNAGAR_FIRMWARE_ID1 ; 
 int /*<<< orphan*/  LOCHNAGAR_FIRMWARE_ID2 ; 
 unsigned int LOCHNAGAR_REV_ID_MASK ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct lochnagar*) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct lochnagar* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 struct gpio_desc* devm_regmap_init_i2c (struct i2c_client*,TYPE_1__*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 int /*<<< orphan*/  lochnagar_of_match ; 
 int lochnagar_wait_for_boot (struct gpio_desc*,unsigned int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int regmap_read (struct gpio_desc*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (struct gpio_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lochnagar_i2c_probe(struct i2c_client *i2c)
{
	struct device *dev = &i2c->dev;
	const struct lochnagar_config *config = NULL;
	const struct of_device_id *of_id;
	struct lochnagar *lochnagar;
	struct gpio_desc *reset, *present;
	unsigned int val;
	unsigned int firmwareid;
	unsigned int devid, rev;
	int ret;

	lochnagar = devm_kzalloc(dev, sizeof(*lochnagar), GFP_KERNEL);
	if (!lochnagar)
		return -ENOMEM;

	of_id = of_match_device(lochnagar_of_match, dev);
	if (!of_id)
		return -EINVAL;

	config = of_id->data;

	lochnagar->dev = dev;
	mutex_init(&lochnagar->analogue_config_lock);

	dev_set_drvdata(dev, lochnagar);

	reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(reset)) {
		ret = PTR_ERR(reset);
		dev_err(dev, "Failed to get reset GPIO: %d\n", ret);
		return ret;
	}

	present = devm_gpiod_get_optional(dev, "present", GPIOD_OUT_HIGH);
	if (IS_ERR(present)) {
		ret = PTR_ERR(present);
		dev_err(dev, "Failed to get present GPIO: %d\n", ret);
		return ret;
	}

	/* Leave the Lochnagar in reset for a reasonable amount of time */
	msleep(20);

	/* Bring Lochnagar out of reset */
	gpiod_set_value_cansleep(reset, 1);

	/* Identify Lochnagar */
	lochnagar->type = config->type;

	lochnagar->regmap = devm_regmap_init_i2c(i2c, config->regmap);
	if (IS_ERR(lochnagar->regmap)) {
		ret = PTR_ERR(lochnagar->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		return ret;
	}

	/* Wait for Lochnagar to boot */
	ret = lochnagar_wait_for_boot(lochnagar->regmap, &val);
	if (ret < 0) {
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		return ret;
	}

	devid = val & LOCHNAGAR_DEVICE_ID_MASK;
	rev = val & LOCHNAGAR_REV_ID_MASK;

	if (devid != config->id) {
		dev_err(dev,
			"ID does not match %s (expected 0x%x got 0x%x)\n",
			config->name, config->id, devid);
		return -ENODEV;
	}

	/* Identify firmware */
	ret = regmap_read(lochnagar->regmap, LOCHNAGAR_FIRMWARE_ID1, &val);
	if (ret < 0) {
		dev_err(dev, "Failed to read firmware id 1: %d\n", ret);
		return ret;
	}

	firmwareid = val;

	ret = regmap_read(lochnagar->regmap, LOCHNAGAR_FIRMWARE_ID2, &val);
	if (ret < 0) {
		dev_err(dev, "Failed to read firmware id 2: %d\n", ret);
		return ret;
	}

	firmwareid |= (val << config->regmap->val_bits);

	dev_info(dev, "Found %s (0x%x) revision %u firmware 0x%.6x\n",
		 config->name, devid, rev + 1, firmwareid);

	ret = regmap_register_patch(lochnagar->regmap, config->patch,
				    config->npatch);
	if (ret < 0) {
		dev_err(dev, "Failed to register patch: %d\n", ret);
		return ret;
	}

	ret = devm_of_platform_populate(dev);
	if (ret < 0) {
		dev_err(dev, "Failed to populate child nodes: %d\n", ret);
		return ret;
	}

	return ret;
}