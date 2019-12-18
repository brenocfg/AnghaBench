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
struct ucs1002_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int F_CHG_ACT ; 
 int /*<<< orphan*/  UCS1002_REG_OTHER_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ucs1002_get_online(struct ucs1002_info *info,
			      union power_supply_propval *val)
{
	unsigned int reg;
	int ret;

	ret = regmap_read(info->regmap, UCS1002_REG_OTHER_STATUS, &reg);
	if (ret)
		return ret;

	val->intval = !!(reg & F_CHG_ACT);

	return 0;
}