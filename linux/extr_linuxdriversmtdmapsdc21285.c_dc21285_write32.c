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
typedef  int /*<<< orphan*/  uint32_t ;
struct map_info {scalar_t__ virt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 scalar_t__ machine_is_netwinder () ; 
 int /*<<< orphan*/  nw_en_write () ; 

__attribute__((used)) static void dc21285_write32(struct map_info *map, const map_word d, unsigned long adr)
{
	if (machine_is_netwinder())
		nw_en_write();
	*(uint32_t*)(map->virt + adr) = d.x[0];
}