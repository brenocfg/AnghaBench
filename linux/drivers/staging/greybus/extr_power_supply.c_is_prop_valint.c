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
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int POWER_SUPPLY_PROP_MODEL_NAME ; 

__attribute__((used)) static int is_prop_valint(enum power_supply_property psp)
{
	return ((psp < POWER_SUPPLY_PROP_MODEL_NAME) ? 1 : 0);
}