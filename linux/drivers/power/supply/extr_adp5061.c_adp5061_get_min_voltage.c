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
union power_supply_propval {int intval; } ;
struct adp5061_state {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5061_VOLTAGE_TH ; 
 unsigned int ADP5061_VOLTAGE_TH_VTRK_DEAD_MSK ; 
 int* adp5061_vmin ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int adp5061_get_min_voltage(struct adp5061_state *st,
				   union power_supply_propval *val)
{
	unsigned int regval;
	int ret;

	ret = regmap_read(st->regmap, ADP5061_VOLTAGE_TH, &regval);
	if (ret < 0)
		return ret;

	regval = ((regval & ADP5061_VOLTAGE_TH_VTRK_DEAD_MSK) >> 3);
	val->intval = adp5061_vmin[regval] * 1000;

	return ret;
}