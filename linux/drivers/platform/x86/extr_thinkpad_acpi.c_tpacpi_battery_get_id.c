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
struct TYPE_2__ {scalar_t__ battery_force_primary; } ;

/* Variables and functions */
 int BAT_PRIMARY ; 
 int BAT_SECONDARY ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static int tpacpi_battery_get_id(const char *battery_name)
{

	if (strcmp(battery_name, "BAT0") == 0 ||
	    tp_features.battery_force_primary)
		return BAT_PRIMARY;
	if (strcmp(battery_name, "BAT1") == 0)
		return BAT_SECONDARY;
	/*
	 * If for some reason the battery is not BAT0 nor is it
	 * BAT1, we will assume it's the default, first battery,
	 * AKA primary.
	 */
	pr_warn("unknown battery %s, assuming primary", battery_name);
	return BAT_PRIMARY;
}