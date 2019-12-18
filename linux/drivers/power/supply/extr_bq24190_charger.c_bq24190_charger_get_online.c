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
 int /*<<< orphan*/  BQ24190_REG_MOC ; 
 int /*<<< orphan*/  BQ24190_REG_MOC_BATFET_DISABLE_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_MOC_BATFET_DISABLE_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_SS ; 
 int /*<<< orphan*/  BQ24190_REG_SS_PG_STAT_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_SS_PG_STAT_SHIFT ; 
 int bq24190_read_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int bq24190_charger_get_online(struct bq24190_dev_info *bdi,
		union power_supply_propval *val)
{
	u8 pg_stat, batfet_disable;
	int ret;

	ret = bq24190_read_mask(bdi, BQ24190_REG_SS,
			BQ24190_REG_SS_PG_STAT_MASK,
			BQ24190_REG_SS_PG_STAT_SHIFT, &pg_stat);
	if (ret < 0)
		return ret;

	ret = bq24190_read_mask(bdi, BQ24190_REG_MOC,
			BQ24190_REG_MOC_BATFET_DISABLE_MASK,
			BQ24190_REG_MOC_BATFET_DISABLE_SHIFT, &batfet_disable);
	if (ret < 0)
		return ret;

	val->intval = pg_stat && !batfet_disable;

	return 0;
}