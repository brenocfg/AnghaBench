#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regulator_init_data {int dummy; } ;
struct regulator_desc {int n_voltages; int min_uV; int uV_step; int enable_val; int disable_val; int enable_time; int /*<<< orphan*/ * ops; void* volt_table; int /*<<< orphan*/  vsel_reg; } ;
struct regulator_config {int /*<<< orphan*/  of_node; struct pfuze_chip* driver_data; struct regulator_init_data* init_data; TYPE_2__* dev; } ;
struct pfuze_regulator_platform_data {struct regulator_init_data** init_data; } ;
struct pfuze_chip {int chip_id; int flags; int /*<<< orphan*/ * regulators; TYPE_4__* pfuze_regulators; TYPE_3__* regulator_descs; int /*<<< orphan*/  regmap; TYPE_2__* dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_11__ {scalar_t__ of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct TYPE_10__ {int name; } ;
struct TYPE_13__ {TYPE_1__ desc; } ;
struct TYPE_12__ {scalar_t__ sw_reg; struct regulator_desc desc; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  PFUZE100 131 
 int PFUZE100_SW2 ; 
 int PFUZE100_SW4 ; 
#define  PFUZE200 130 
 int PFUZE200_SW2 ; 
 int PFUZE200_SW3B ; 
#define  PFUZE3000 129 
 int PFUZE3000_SW2 ; 
#define  PFUZE3001 128 
 int PFUZE3001_SW2 ; 
 int PFUZE_FLAG_DISABLE_SW ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct pfuze_regulator_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,char*) ; 
 struct pfuze_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_2__*,struct regulator_desc*,struct regulator_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pfuze_chip*) ; 
 struct regulator_init_data* match_init_data (int) ; 
 int /*<<< orphan*/  match_of_node (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_4__*,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (scalar_t__,char*) ; 
 void* pfuze100_regulators ; 
 int /*<<< orphan*/  pfuze100_sw_disable_regulator_ops ; 
 void* pfuze200_regulators ; 
 void* pfuze3000_regulators ; 
 void* pfuze3000_sw2hi ; 
 void* pfuze3001_regulators ; 
 int /*<<< orphan*/  pfuze_dt_ids ; 
 int pfuze_identify (struct pfuze_chip*) ; 
 int pfuze_parse_regulators_dt (struct pfuze_chip*) ; 
 int pfuze_power_off_prepare_init (struct pfuze_chip*) ; 
 int /*<<< orphan*/  pfuze_regmap_config ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pfuze100_regulator_probe(struct i2c_client *client,
				    const struct i2c_device_id *id)
{
	struct pfuze_chip *pfuze_chip;
	struct pfuze_regulator_platform_data *pdata =
	    dev_get_platdata(&client->dev);
	struct regulator_config config = { };
	int i, ret;
	const struct of_device_id *match;
	u32 regulator_num;
	u32 sw_check_start, sw_check_end, sw_hi = 0x40;

	pfuze_chip = devm_kzalloc(&client->dev, sizeof(*pfuze_chip),
			GFP_KERNEL);
	if (!pfuze_chip)
		return -ENOMEM;

	if (client->dev.of_node) {
		match = of_match_device(of_match_ptr(pfuze_dt_ids),
				&client->dev);
		if (!match) {
			dev_err(&client->dev, "Error: No device match found\n");
			return -ENODEV;
		}
		pfuze_chip->chip_id = (int)(long)match->data;
	} else if (id) {
		pfuze_chip->chip_id = id->driver_data;
	} else {
		dev_err(&client->dev, "No dts match or id table match found\n");
		return -ENODEV;
	}

	i2c_set_clientdata(client, pfuze_chip);
	pfuze_chip->dev = &client->dev;

	pfuze_chip->regmap = devm_regmap_init_i2c(client, &pfuze_regmap_config);
	if (IS_ERR(pfuze_chip->regmap)) {
		ret = PTR_ERR(pfuze_chip->regmap);
		dev_err(&client->dev,
			"regmap allocation failed with err %d\n", ret);
		return ret;
	}

	ret = pfuze_identify(pfuze_chip);
	if (ret) {
		dev_err(&client->dev, "unrecognized pfuze chip ID!\n");
		return ret;
	}

	/* use the right regulators after identify the right device */
	switch (pfuze_chip->chip_id) {
	case PFUZE3001:
		pfuze_chip->pfuze_regulators = pfuze3001_regulators;
		regulator_num = ARRAY_SIZE(pfuze3001_regulators);
		sw_check_start = PFUZE3001_SW2;
		sw_check_end = PFUZE3001_SW2;
		sw_hi = 1 << 3;
		break;
	case PFUZE3000:
		pfuze_chip->pfuze_regulators = pfuze3000_regulators;
		regulator_num = ARRAY_SIZE(pfuze3000_regulators);
		sw_check_start = PFUZE3000_SW2;
		sw_check_end = PFUZE3000_SW2;
		sw_hi = 1 << 3;
		break;
	case PFUZE200:
		pfuze_chip->pfuze_regulators = pfuze200_regulators;
		regulator_num = ARRAY_SIZE(pfuze200_regulators);
		sw_check_start = PFUZE200_SW2;
		sw_check_end = PFUZE200_SW3B;
		break;
	case PFUZE100:
	default:
		pfuze_chip->pfuze_regulators = pfuze100_regulators;
		regulator_num = ARRAY_SIZE(pfuze100_regulators);
		sw_check_start = PFUZE100_SW2;
		sw_check_end = PFUZE100_SW4;
		break;
	}
	dev_info(&client->dev, "pfuze%s found.\n",
		(pfuze_chip->chip_id == PFUZE100) ? "100" :
		(((pfuze_chip->chip_id == PFUZE200) ? "200" :
		((pfuze_chip->chip_id == PFUZE3000) ? "3000" : "3001"))));

	memcpy(pfuze_chip->regulator_descs, pfuze_chip->pfuze_regulators,
		sizeof(pfuze_chip->regulator_descs));

	ret = pfuze_parse_regulators_dt(pfuze_chip);
	if (ret)
		return ret;

	for (i = 0; i < regulator_num; i++) {
		struct regulator_init_data *init_data;
		struct regulator_desc *desc;
		int val;

		desc = &pfuze_chip->regulator_descs[i].desc;

		if (pdata)
			init_data = pdata->init_data[i];
		else
			init_data = match_init_data(i);

		/* SW2~SW4 high bit check and modify the voltage value table */
		if (i >= sw_check_start && i <= sw_check_end) {
			ret = regmap_read(pfuze_chip->regmap,
						desc->vsel_reg, &val);
			if (ret) {
				dev_err(&client->dev, "Fails to read from the register.\n");
				return ret;
			}

			if (val & sw_hi) {
				if (pfuze_chip->chip_id == PFUZE3000 ||
					pfuze_chip->chip_id == PFUZE3001) {
					desc->volt_table = pfuze3000_sw2hi;
					desc->n_voltages = ARRAY_SIZE(pfuze3000_sw2hi);
				} else {
					desc->min_uV = 800000;
					desc->uV_step = 50000;
					desc->n_voltages = 51;
				}
			}
		}

		/*
		 * Allow SW regulators to turn off. Checking it trough a flag is
		 * a workaround to keep the backward compatibility with existing
		 * old dtb's which may relay on the fact that we didn't disable
		 * the switched regulator till yet.
		 */
		if (pfuze_chip->flags & PFUZE_FLAG_DISABLE_SW) {
			if (pfuze_chip->regulator_descs[i].sw_reg) {
				desc->ops = &pfuze100_sw_disable_regulator_ops;
				desc->enable_val = 0x8;
				desc->disable_val = 0x0;
				desc->enable_time = 500;
			}
		}

		config.dev = &client->dev;
		config.init_data = init_data;
		config.driver_data = pfuze_chip;
		config.of_node = match_of_node(i);

		pfuze_chip->regulators[i] =
			devm_regulator_register(&client->dev, desc, &config);
		if (IS_ERR(pfuze_chip->regulators[i])) {
			dev_err(&client->dev, "register regulator%s failed\n",
				pfuze_chip->pfuze_regulators[i].desc.name);
			return PTR_ERR(pfuze_chip->regulators[i]);
		}
	}

	if (of_property_read_bool(client->dev.of_node,
				  "fsl,pmic-stby-poweroff"))
		return pfuze_power_off_prepare_init(pfuze_chip);

	return 0;
}