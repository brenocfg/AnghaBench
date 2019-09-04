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
typedef  int /*<<< orphan*/  u16 ;
struct map_info {int /*<<< orphan*/  virt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 int /*<<< orphan*/  ADRS (unsigned long) ; 
 int /*<<< orphan*/  cobalt_bus_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flash_write16(struct map_info *map, const map_word datum,
			  unsigned long offset)
{
	u16 data = (u16)datum.x[0];

	cobalt_bus_write16(map->virt, ADRS(offset), data);
}