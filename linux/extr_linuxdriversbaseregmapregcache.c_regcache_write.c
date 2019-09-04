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
struct regmap {scalar_t__ cache_type; TYPE_1__* cache_ops; } ;
struct TYPE_2__ {int (* write ) (struct regmap*,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ REGCACHE_NONE ; 
 int /*<<< orphan*/  regmap_volatile (struct regmap*,unsigned int) ; 
 int stub1 (struct regmap*,unsigned int,unsigned int) ; 

int regcache_write(struct regmap *map,
		   unsigned int reg, unsigned int value)
{
	if (map->cache_type == REGCACHE_NONE)
		return 0;

	BUG_ON(!map->cache_ops);

	if (!regmap_volatile(map, reg))
		return map->cache_ops->write(map, reg, value);

	return 0;
}