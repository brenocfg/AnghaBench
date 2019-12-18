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
struct rt9455_info {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rt9455_ichrg_values ; 

__attribute__((used)) static int rt9455_charger_get_current_max(struct rt9455_info *info,
					  union power_supply_propval *val)
{
	int idx = ARRAY_SIZE(rt9455_ichrg_values) - 1;

	val->intval = rt9455_ichrg_values[idx];

	return 0;
}