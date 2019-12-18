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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct ucs1002_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int UCS1002_ILIM_SW_MASK ; 
 int /*<<< orphan*/  UCS1002_REG_ILIMIT ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/ * ucs1002_current_limit_uA ; 

__attribute__((used)) static int ucs1002_get_max_current(struct ucs1002_info *info,
				   union power_supply_propval *val)
{
	unsigned int reg;
	int ret;

	ret = regmap_read(info->regmap, UCS1002_REG_ILIMIT, &reg);
	if (ret)
		return ret;

	val->intval = ucs1002_current_limit_uA[reg & UCS1002_ILIM_SW_MASK];

	return 0;
}