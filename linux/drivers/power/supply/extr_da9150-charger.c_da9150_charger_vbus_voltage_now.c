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
struct da9150_charger {int /*<<< orphan*/  vbus_chan; } ;

/* Variables and functions */
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int da9150_charger_vbus_voltage_now(struct da9150_charger *charger,
					   union power_supply_propval *val)
{
	int v_val, ret;

	/* Read processed value - mV units */
	ret = iio_read_channel_processed(charger->vbus_chan, &v_val);
	if (ret < 0)
		return ret;

	/* Convert voltage to expected uV units */
	val->intval = v_val * 1000;

	return 0;
}