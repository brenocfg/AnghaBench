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
struct ti_ads7950_state {int vref_mv; int cmd_settings_bitmask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int TI_ADS7950_CR_RANGE_5V ; 
 int regulator_get_voltage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_ads7950_get_range(struct ti_ads7950_state *st)
{
	int vref;

	if (st->vref_mv) {
		vref = st->vref_mv;
	} else {
		vref = regulator_get_voltage(st->reg);
		if (vref < 0)
			return vref;

		vref /= 1000;
	}

	if (st->cmd_settings_bitmask & TI_ADS7950_CR_RANGE_5V)
		vref *= 2;

	return vref;
}