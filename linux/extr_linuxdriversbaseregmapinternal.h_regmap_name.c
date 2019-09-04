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
struct regmap {char const* name; scalar_t__ dev; } ;

/* Variables and functions */
 char const* dev_name (scalar_t__) ; 

__attribute__((used)) static inline const char *regmap_name(const struct regmap *map)
{
	if (map->dev)
		return dev_name(map->dev);

	return map->name;
}