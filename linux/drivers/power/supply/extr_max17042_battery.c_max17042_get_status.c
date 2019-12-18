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
typedef  int u32 ;
struct max17042_chip {TYPE_1__* pdata; int /*<<< orphan*/  regmap; int /*<<< orphan*/  battery; } ;
struct TYPE_2__ {int r_sns; int /*<<< orphan*/  enable_current_sense; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_AvgCurrent ; 
 int MAX17042_FULL_THRESHOLD ; 
 int /*<<< orphan*/  MAX17042_FullCAP ; 
 int /*<<< orphan*/  MAX17042_RepCap ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int power_supply_am_i_supplied (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int max17042_get_status(struct max17042_chip *chip, int *status)
{
	int ret, charge_full, charge_now;
	int avg_current;
	u32 data;

	ret = power_supply_am_i_supplied(chip->battery);
	if (ret < 0) {
		*status = POWER_SUPPLY_STATUS_UNKNOWN;
		return 0;
	}
	if (ret == 0) {
		*status = POWER_SUPPLY_STATUS_DISCHARGING;
		return 0;
	}

	/*
	 * The MAX170xx has builtin end-of-charge detection and will update
	 * FullCAP to match RepCap when it detects end of charging.
	 *
	 * When this cycle the battery gets charged to a higher (calculated)
	 * capacity then the previous cycle then FullCAP will get updated
	 * contineously once end-of-charge detection kicks in, so allow the
	 * 2 to differ a bit.
	 */

	ret = regmap_read(chip->regmap, MAX17042_FullCAP, &charge_full);
	if (ret < 0)
		return ret;

	ret = regmap_read(chip->regmap, MAX17042_RepCap, &charge_now);
	if (ret < 0)
		return ret;

	if ((charge_full - charge_now) <= MAX17042_FULL_THRESHOLD) {
		*status = POWER_SUPPLY_STATUS_FULL;
		return 0;
	}

	/*
	 * Even though we are supplied, we may still be discharging if the
	 * supply is e.g. only delivering 5V 0.5A. Check current if available.
	 */
	if (!chip->pdata->enable_current_sense) {
		*status = POWER_SUPPLY_STATUS_CHARGING;
		return 0;
	}

	ret = regmap_read(chip->regmap, MAX17042_AvgCurrent, &data);
	if (ret < 0)
		return ret;

	avg_current = sign_extend32(data, 15);
	avg_current *= 1562500 / chip->pdata->r_sns;

	if (avg_current > 0)
		*status = POWER_SUPPLY_STATUS_CHARGING;
	else
		*status = POWER_SUPPLY_STATUS_DISCHARGING;

	return 0;
}