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
typedef  scalar_t__ u8 ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BQ24190_REG_CCC ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_ICHG_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_ICHG_SHIFT ; 
 int /*<<< orphan*/  bq24190_ccc_ichg_values ; 
 int bq24190_get_field_val (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int bq24190_read_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int bq24190_charger_get_current(struct bq24190_dev_info *bdi,
		union power_supply_propval *val)
{
	u8 v;
	int curr, ret;

	ret = bq24190_get_field_val(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_ICHG_MASK, BQ24190_REG_CCC_ICHG_SHIFT,
			bq24190_ccc_ichg_values,
			ARRAY_SIZE(bq24190_ccc_ichg_values), &curr);
	if (ret < 0)
		return ret;

	ret = bq24190_read_mask(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_FORCE_20PCT_MASK,
			BQ24190_REG_CCC_FORCE_20PCT_SHIFT, &v);
	if (ret < 0)
		return ret;

	/* If FORCE_20PCT is enabled, then current is 20% of ICHG value */
	if (v)
		curr /= 5;

	val->intval = curr;
	return 0;
}