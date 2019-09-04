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
struct TYPE_2__ {unsigned int (* parse_val ) (void const*) ;} ;
struct regmap {TYPE_1__ format; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int stub1 (void const*) ; 

int regmap_parse_val(struct regmap *map, const void *buf,
			unsigned int *val)
{
	if (!map->format.parse_val)
		return -EINVAL;

	*val = map->format.parse_val(buf);

	return 0;
}