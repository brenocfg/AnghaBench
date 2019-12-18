#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map_info {int /*<<< orphan*/  virt; } ;
struct TYPE_3__ {int* x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 int /*<<< orphan*/  ADRS (unsigned long) ; 
 int cobalt_bus_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static map_word flash_read16(struct map_info *map, unsigned long offset)
{
	map_word r;

	r.x[0] = cobalt_bus_read32(map->virt, ADRS(offset));
	if (offset & 0x2)
		r.x[0] >>= 16;
	else
		r.x[0] &= 0x0000ffff;

	return r;
}