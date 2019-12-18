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
struct regulator_supply_alias {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct regulator_supply_alias*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct regulator_supply_alias* regulator_find_supply_alias (struct device*,char const*) ; 

void regulator_unregister_supply_alias(struct device *dev, const char *id)
{
	struct regulator_supply_alias *map;

	map = regulator_find_supply_alias(dev, id);
	if (map) {
		list_del(&map->list);
		kfree(map);
	}
}