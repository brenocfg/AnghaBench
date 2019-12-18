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
typedef  int /*<<< orphan*/  u8 ;
struct adp5061_state {int dummy; } ;

/* Variables and functions */
#define  ADP5061_CHG_COMPLETE 133 
#define  ADP5061_CHG_FAST_CC 132 
#define  ADP5061_CHG_FAST_CV 131 
#define  ADP5061_CHG_OFF 130 
 int ADP5061_CHG_STATUS_1_CHG_STATUS (int /*<<< orphan*/ ) ; 
#define  ADP5061_CHG_TIMER_EXP 129 
#define  ADP5061_CHG_TRICKLE 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_FULL ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int adp5061_get_status (struct adp5061_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adp5061_get_charger_status(struct adp5061_state *st,
				      union power_supply_propval *val)
{
	u8 status1, status2;
	int ret;

	ret = adp5061_get_status(st, &status1, &status2);
	if (ret < 0)
		return ret;

	switch (ADP5061_CHG_STATUS_1_CHG_STATUS(status1)) {
	case ADP5061_CHG_OFF:
		val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	case ADP5061_CHG_TRICKLE:
	case ADP5061_CHG_FAST_CC:
	case ADP5061_CHG_FAST_CV:
		val->intval = POWER_SUPPLY_STATUS_CHARGING;
		break;
	case ADP5061_CHG_COMPLETE:
		val->intval = POWER_SUPPLY_STATUS_FULL;
		break;
	case ADP5061_CHG_TIMER_EXP:
		/* The battery must be discharging if there is a charge fault */
		val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	default:
		val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
	}

	return ret;
}