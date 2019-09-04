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
struct regmap {TYPE_1__* reg_defaults; int /*<<< orphan*/  no_sync_defaults; } ;
struct TYPE_2__ {unsigned int def; } ;

/* Variables and functions */
 int regcache_lookup_reg (struct regmap*,unsigned int) ; 

__attribute__((used)) static bool regcache_reg_needs_sync(struct regmap *map, unsigned int reg,
				    unsigned int val)
{
	int ret;

	/* If we don't know the chip just got reset, then sync everything. */
	if (!map->no_sync_defaults)
		return true;

	/* Is this the hardware default?  If so skip. */
	ret = regcache_lookup_reg(map, reg);
	if (ret >= 0 && val == map->reg_defaults[ret].def)
		return false;
	return true;
}