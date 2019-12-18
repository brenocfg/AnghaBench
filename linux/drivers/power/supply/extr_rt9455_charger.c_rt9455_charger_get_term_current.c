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
struct rt9455_info {TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_ICHRG ; 
 int /*<<< orphan*/  F_IEOC_PERCENTAGE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rt9455_get_field_val (struct rt9455_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt9455_ichrg_values ; 
 int /*<<< orphan*/  rt9455_ieoc_percentage_values ; 

__attribute__((used)) static int rt9455_charger_get_term_current(struct rt9455_info *info,
					   union power_supply_propval *val)
{
	struct device *dev = &info->client->dev;
	int ichrg, ieoc_percentage, ret;

	ret = rt9455_get_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values),
				   &ichrg);
	if (ret) {
		dev_err(dev, "Failed to read ICHRG value\n");
		return ret;
	}

	ret = rt9455_get_field_val(info, F_IEOC_PERCENTAGE,
				   rt9455_ieoc_percentage_values,
				   ARRAY_SIZE(rt9455_ieoc_percentage_values),
				   &ieoc_percentage);
	if (ret) {
		dev_err(dev, "Failed to read IEOC value\n");
		return ret;
	}

	val->intval = ichrg * ieoc_percentage / 100;

	return 0;
}