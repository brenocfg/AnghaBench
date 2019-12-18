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
struct value_to_name_map {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static const char *value_to_name(struct value_to_name_map *table, int count,
				 int value)
{
	if (value >= count)
		return "unknown";
	return table[value].name;
}