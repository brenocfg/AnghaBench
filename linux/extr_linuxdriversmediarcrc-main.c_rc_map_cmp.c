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
struct rc_map_table {unsigned int const scancode; } ;

/* Variables and functions */

__attribute__((used)) static int rc_map_cmp(const void *key, const void *elt)
{
	const unsigned int *scancode = key;
	const struct rc_map_table *e = elt;

	if (*scancode < e->scancode)
		return -1;
	else if (*scancode > e->scancode)
		return 1;
	return 0;
}