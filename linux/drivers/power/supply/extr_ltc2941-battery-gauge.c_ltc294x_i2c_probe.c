#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct power_supply_config {struct ltc294x_info* drv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * external_power_changed; int /*<<< orphan*/  property_is_writeable; int /*<<< orphan*/  set_property; int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct ltc294x_info {int id; int r_sense; int Qlsb; int /*<<< orphan*/  work; int /*<<< orphan*/  supply; TYPE_2__ supply_desc; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int s32 ;
typedef  enum ltc294x_id { ____Placeholder_ltc294x_id } ltc294x_id ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  LTC2941_ID 131 
 int LTC2941_MAX_PRESCALER_EXP ; 
 int LTC2941_REG_STATUS_CHIP_ID ; 
#define  LTC2942_ID 130 
#define  LTC2943_ID 129 
 int LTC2943_MAX_PRESCALER_EXP ; 
#define  LTC2944_ID 128 
 int /*<<< orphan*/  LTC294X_REG_STATUS ; 
 int LTC294X_WORK_DELAY ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 struct ltc294x_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ltc294x_info*) ; 
 int /*<<< orphan*/  ltc294x_get_property ; 
 int /*<<< orphan*/  ltc294x_properties ; 
 int /*<<< orphan*/  ltc294x_property_is_writeable ; 
 int ltc294x_read_regs (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 
 int ltc294x_reset (struct ltc294x_info*,int) ; 
 int /*<<< orphan*/  ltc294x_set_property ; 
 int /*<<< orphan*/  ltc294x_work ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  power_supply_register (TYPE_1__*,TYPE_2__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ltc294x_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	struct power_supply_config psy_cfg = {};
	struct ltc294x_info *info;
	struct device_node *np;
	int ret;
	u32 prescaler_exp;
	s32 r_sense;
	u8 status;

	info = devm_kzalloc(&client->dev, sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		return -ENOMEM;

	i2c_set_clientdata(client, info);

	np = of_node_get(client->dev.of_node);

	info->id = (enum ltc294x_id)of_device_get_match_data(&client->dev);
	info->supply_desc.name = np->name;

	/* r_sense can be negative, when sense+ is connected to the battery
	 * instead of the sense-. This results in reversed measurements. */
	ret = of_property_read_u32(np, "lltc,resistor-sense", &r_sense);
	if (ret < 0) {
		dev_err(&client->dev,
			"Could not find lltc,resistor-sense in devicetree\n");
		return ret;
	}
	info->r_sense = r_sense;

	ret = of_property_read_u32(np, "lltc,prescaler-exponent",
		&prescaler_exp);
	if (ret < 0) {
		dev_warn(&client->dev,
			"lltc,prescaler-exponent not in devicetree\n");
		prescaler_exp = LTC2941_MAX_PRESCALER_EXP;
	}

	if (info->id == LTC2943_ID) {
		if (prescaler_exp > LTC2943_MAX_PRESCALER_EXP)
			prescaler_exp = LTC2943_MAX_PRESCALER_EXP;
		info->Qlsb = ((340 * 50000) / r_sense) /
				(4096 / (1 << (2*prescaler_exp)));
	} else {
		if (prescaler_exp > LTC2941_MAX_PRESCALER_EXP)
			prescaler_exp = LTC2941_MAX_PRESCALER_EXP;
		info->Qlsb = ((85 * 50000) / r_sense) /
				(128 / (1 << prescaler_exp));
	}

	/* Read status register to check for LTC2942 */
	if (info->id == LTC2941_ID || info->id == LTC2942_ID) {
		ret = ltc294x_read_regs(client, LTC294X_REG_STATUS, &status, 1);
		if (ret < 0) {
			dev_err(&client->dev,
				"Could not read status register\n");
			return ret;
		}
		if (status & LTC2941_REG_STATUS_CHIP_ID)
			info->id = LTC2941_ID;
		else
			info->id = LTC2942_ID;
	}

	info->client = client;
	info->supply_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	info->supply_desc.properties = ltc294x_properties;
	switch (info->id) {
	case LTC2944_ID:
	case LTC2943_ID:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties);
		break;
	case LTC2942_ID:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties) - 1;
		break;
	case LTC2941_ID:
	default:
		info->supply_desc.num_properties =
			ARRAY_SIZE(ltc294x_properties) - 3;
		break;
	}
	info->supply_desc.get_property = ltc294x_get_property;
	info->supply_desc.set_property = ltc294x_set_property;
	info->supply_desc.property_is_writeable = ltc294x_property_is_writeable;
	info->supply_desc.external_power_changed	= NULL;

	psy_cfg.drv_data = info;

	INIT_DELAYED_WORK(&info->work, ltc294x_work);

	ret = ltc294x_reset(info, prescaler_exp);
	if (ret < 0) {
		dev_err(&client->dev, "Communication with chip failed\n");
		return ret;
	}

	info->supply = power_supply_register(&client->dev, &info->supply_desc,
					     &psy_cfg);
	if (IS_ERR(info->supply)) {
		dev_err(&client->dev, "failed to register ltc2941\n");
		return PTR_ERR(info->supply);
	} else {
		schedule_delayed_work(&info->work, LTC294X_WORK_DELAY * HZ);
	}

	return 0;
}