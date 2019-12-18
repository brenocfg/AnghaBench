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
struct aiptek_map {int value; scalar_t__ string; } ;

/* Variables and functions */
 int AIPTEK_INVALID_VALUE ; 
 int /*<<< orphan*/  strncmp (char const*,scalar_t__,size_t) ; 

__attribute__((used)) static int map_str_to_val(const struct aiptek_map *map, const char *str, size_t count)
{
	const struct aiptek_map *p;

	if (str[count - 1] == '\n')
		count--;

	for (p = map; p->string; p++)
	        if (!strncmp(str, p->string, count))
			return p->value;

	return AIPTEK_INVALID_VALUE;
}