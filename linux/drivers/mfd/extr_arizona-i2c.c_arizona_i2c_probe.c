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
struct regmap_config {int dummy; } ;
struct i2c_device_id {unsigned long driver_data; } ;
struct TYPE_4__ {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_1__ dev; } ;
struct arizona {unsigned long type; int /*<<< orphan*/  irq; TYPE_1__* dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MFD_WM5102 ; 
 int /*<<< orphan*/  CONFIG_MFD_WM5110 ; 
 int /*<<< orphan*/  CONFIG_MFD_WM8997 ; 
 int /*<<< orphan*/  CONFIG_MFD_WM8998 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  WM1814 133 
#define  WM5102 132 
#define  WM5110 131 
#define  WM8280 130 
#define  WM8997 129 
#define  WM8998 128 
 int arizona_dev_init (struct arizona*) ; 
 unsigned long arizona_of_get_type (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct arizona* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 struct regmap_config wm5102_i2c_regmap ; 
 struct regmap_config wm5110_i2c_regmap ; 
 struct regmap_config wm8997_i2c_regmap ; 
 struct regmap_config wm8998_i2c_regmap ; 

__attribute__((used)) static int arizona_i2c_probe(struct i2c_client *i2c,
			     const struct i2c_device_id *id)
{
	struct arizona *arizona;
	const struct regmap_config *regmap_config = NULL;
	unsigned long type;
	int ret;

	if (i2c->dev.of_node)
		type = arizona_of_get_type(&i2c->dev);
	else
		type = id->driver_data;

	switch (type) {
	case WM5102:
		if (IS_ENABLED(CONFIG_MFD_WM5102))
			regmap_config = &wm5102_i2c_regmap;
		break;
	case WM5110:
	case WM8280:
		if (IS_ENABLED(CONFIG_MFD_WM5110))
			regmap_config = &wm5110_i2c_regmap;
		break;
	case WM8997:
		if (IS_ENABLED(CONFIG_MFD_WM8997))
			regmap_config = &wm8997_i2c_regmap;
		break;
	case WM8998:
	case WM1814:
		if (IS_ENABLED(CONFIG_MFD_WM8998))
			regmap_config = &wm8998_i2c_regmap;
		break;
	default:
		dev_err(&i2c->dev, "Unknown device type %ld\n", type);
		return -EINVAL;
	}

	if (!regmap_config) {
		dev_err(&i2c->dev,
			"No kernel support for device type %ld\n", type);
		return -EINVAL;
	}

	arizona = devm_kzalloc(&i2c->dev, sizeof(*arizona), GFP_KERNEL);
	if (arizona == NULL)
		return -ENOMEM;

	arizona->regmap = devm_regmap_init_i2c(i2c, regmap_config);
	if (IS_ERR(arizona->regmap)) {
		ret = PTR_ERR(arizona->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	arizona->type = type;
	arizona->dev = &i2c->dev;
	arizona->irq = i2c->irq;

	return arizona_dev_init(arizona);
}