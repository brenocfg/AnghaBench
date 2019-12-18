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
struct i2c_client {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int POWER_SUPPLY_PROP_PRESENT ; 
 size_t REG_STATUS ; 
 TYPE_1__* sbs_data ; 
 int sbs_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbs_get_battery_presence_and_health(
	struct i2c_client *client, enum power_supply_property psp,
	union power_supply_propval *val)
{
	int ret;

	/* Dummy command; if it succeeds, battery is present. */
	ret = sbs_read_word_data(client, sbs_data[REG_STATUS].addr);

	if (ret < 0) { /* battery not present*/
		if (psp == POWER_SUPPLY_PROP_PRESENT) {
			val->intval = 0;
			return 0;
		}
		return ret;
	}

	if (psp == POWER_SUPPLY_PROP_PRESENT)
		val->intval = 1; /* battery present */
	else /* POWER_SUPPLY_PROP_HEALTH */
		/* SBS spec doesn't have a general health command. */
		val->intval = POWER_SUPPLY_HEALTH_UNKNOWN;

	return 0;
}