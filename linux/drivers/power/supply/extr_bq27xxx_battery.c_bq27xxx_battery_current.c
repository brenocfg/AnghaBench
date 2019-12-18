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
struct bq27xxx_device_info {int opts; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int BQ27000_FLAG_CHGS ; 
 int BQ27XXX_CURRENT_CONSTANT ; 
 int BQ27XXX_O_ZERO ; 
 int /*<<< orphan*/  BQ27XXX_REG_AI ; 
 int /*<<< orphan*/  BQ27XXX_REG_FLAGS ; 
 int BQ27XXX_RS ; 
 int bq27xxx_read (struct bq27xxx_device_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bq27xxx_battery_current(struct bq27xxx_device_info *di,
				   union power_supply_propval *val)
{
	int curr;
	int flags;

	curr = bq27xxx_read(di, BQ27XXX_REG_AI, false);
	if (curr < 0) {
		dev_err(di->dev, "error reading current\n");
		return curr;
	}

	if (di->opts & BQ27XXX_O_ZERO) {
		flags = bq27xxx_read(di, BQ27XXX_REG_FLAGS, true);
		if (flags & BQ27000_FLAG_CHGS) {
			dev_dbg(di->dev, "negative current!\n");
			curr = -curr;
		}

		val->intval = curr * BQ27XXX_CURRENT_CONSTANT / BQ27XXX_RS;
	} else {
		/* Other gauges return signed value */
		val->intval = (int)((s16)curr) * 1000;
	}

	return 0;
}