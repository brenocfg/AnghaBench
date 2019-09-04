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
struct regmap {unsigned int reg_stride_order; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int regcache_get_index_by_order(const struct regmap *map,
						       unsigned int reg)
{
	return reg >> map->reg_stride_order;
}