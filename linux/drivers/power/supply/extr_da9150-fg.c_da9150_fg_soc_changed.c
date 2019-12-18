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
union power_supply_propval {scalar_t__ intval; } ;
struct da9150_fg {scalar_t__ soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  da9150_fg_capacity (struct da9150_fg*,union power_supply_propval*) ; 

__attribute__((used)) static bool da9150_fg_soc_changed(struct da9150_fg *fg)
{
	union power_supply_propval val;

	da9150_fg_capacity(fg, &val);
	if (val.intval != fg->soc) {
		fg->soc = val.intval;
		return true;
	}

	return false;
}