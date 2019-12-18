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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_ICHRG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rt9455_get_field_val (struct rt9455_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt9455_ichrg_values ; 

__attribute__((used)) static int rt9455_charger_get_current(struct rt9455_info *info,
				      union power_supply_propval *val)
{
	int curr;
	int ret;

	ret = rt9455_get_field_val(info, F_ICHRG,
				   rt9455_ichrg_values,
				   ARRAY_SIZE(rt9455_ichrg_values),
				   &curr);
	if (ret) {
		dev_err(&info->client->dev, "Failed to read ICHRG value\n");
		return ret;
	}

	val->intval = curr;

	return 0;
}