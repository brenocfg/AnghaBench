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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct qm1d1b0004_cb_map {scalar_t__ frequency; int cb; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qm1d1b0004_cb_map*) ; 
 struct qm1d1b0004_cb_map* cb_maps ; 

__attribute__((used)) static u8 lookup_cb(u32 frequency)
{
	int i;
	const struct qm1d1b0004_cb_map *map;

	for (i = 0; i < ARRAY_SIZE(cb_maps); i++) {
		map = &cb_maps[i];
		if (frequency < map->frequency)
			return map->cb;
	}
	return 0xc0;
}