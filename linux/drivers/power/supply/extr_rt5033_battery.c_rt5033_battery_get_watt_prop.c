#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct rt5033_battery {int /*<<< orphan*/  regmap; } ;
struct i2c_client {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_OCV 128 
 unsigned int RT5033_FUEL_REG_AVG_VOLT_H ; 
 unsigned int RT5033_FUEL_REG_AVG_VOLT_L ; 
 unsigned int RT5033_FUEL_REG_OCV_H ; 
 unsigned int RT5033_FUEL_REG_OCV_L ; 
 unsigned int RT5033_FUEL_REG_VBAT_H ; 
 unsigned int RT5033_FUEL_REG_VBAT_L ; 
 struct rt5033_battery* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int rt5033_battery_get_watt_prop(struct i2c_client *client,
		enum power_supply_property psp)
{
	struct rt5033_battery *battery = i2c_get_clientdata(client);
	unsigned int regh, regl;
	int ret;
	u32 msb, lsb;

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		regh = RT5033_FUEL_REG_VBAT_H;
		regl = RT5033_FUEL_REG_VBAT_L;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		regh = RT5033_FUEL_REG_AVG_VOLT_H;
		regl = RT5033_FUEL_REG_AVG_VOLT_L;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		regh = RT5033_FUEL_REG_OCV_H;
		regl = RT5033_FUEL_REG_OCV_L;
		break;
	default:
		return -EINVAL;
	}

	regmap_read(battery->regmap, regh, &msb);
	regmap_read(battery->regmap, regl, &lsb);

	ret = ((msb << 4) + (lsb >> 4)) * 1250 / 1000;

	return ret;
}