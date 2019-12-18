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
struct regulator_supply_alias {char const* src_supply; char const* alias_supply; int /*<<< orphan*/  list; struct device* alias_dev; struct device* src_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct regulator_supply_alias* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 struct regulator_supply_alias* regulator_find_supply_alias (struct device*,char const*) ; 
 int /*<<< orphan*/  regulator_supply_alias_list ; 

int regulator_register_supply_alias(struct device *dev, const char *id,
				    struct device *alias_dev,
				    const char *alias_id)
{
	struct regulator_supply_alias *map;

	map = regulator_find_supply_alias(dev, id);
	if (map)
		return -EEXIST;

	map = kzalloc(sizeof(struct regulator_supply_alias), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	map->src_dev = dev;
	map->src_supply = id;
	map->alias_dev = alias_dev;
	map->alias_supply = alias_id;

	list_add(&map->list, &regulator_supply_alias_list);

	pr_info("Adding alias for supply %s,%s -> %s,%s\n",
		id, dev_name(dev), alias_id, dev_name(alias_dev));

	return 0;
}