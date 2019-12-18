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
 int /*<<< orphan*/  ADP5061_TERM_SET ; 
 int ADP5061_TERM_SET_CHG_VLIM_MODE (unsigned int) ; 
 int* adp5061_const_chg_vmax ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int adp5061_get_chg_volt_lim(struct adp5061_state *st,
				    union power_supply_propval *val)
{
	unsigned int regval;
	int mode, ret;

	ret = regmap_read(st->regmap, ADP5061_TERM_SET, &regval);
	if (ret < 0)
		return ret;

	mode = ADP5061_TERM_SET_CHG_VLIM_MODE(regval);
	val->intval = adp5061_const_chg_vmax[mode] * 1000;

	return ret;
}