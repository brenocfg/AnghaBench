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
union power_supply_propval {int intval; } ;
typedef  int u8 ;
struct power_supply {int dummy; } ;
struct max8998_battery_data {TYPE_1__* iodev; } ;
struct i2c_client {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {struct i2c_client* i2c; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX8998_REG_STATUS2 ; 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_PRESENT 128 
 int max8998_read_reg (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 struct max8998_battery_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int max8998_battery_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct max8998_battery_data *max8998 = power_supply_get_drvdata(psy);
	struct i2c_client *i2c = max8998->iodev->i2c;
	int ret;
	u8 reg;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		ret = max8998_read_reg(i2c, MAX8998_REG_STATUS2, &reg);
		if (ret)
			return ret;
		if (reg & (1 << 4))
			val->intval = 0;
		else
			val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = max8998_read_reg(i2c, MAX8998_REG_STATUS2, &reg);
		if (ret)
			return ret;
		if (reg & (1 << 3))
			val->intval = 0;
		else
			val->intval = 1;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}