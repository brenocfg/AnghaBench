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
struct kx_odr_map {int val; int val2; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kx_odr_map const* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct kx_odr_map *kxcjk1013_find_odr_value(
	const struct kx_odr_map *map, size_t map_size, int val, int val2)
{
	int i;

	for (i = 0; i < map_size; ++i) {
		if (map[i].val == val && map[i].val2 == val2)
			return &map[i];
	}

	return ERR_PTR(-EINVAL);
}