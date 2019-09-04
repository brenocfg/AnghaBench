#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr_map; TYPE_1__* map; } ;
struct TYPE_3__ {unsigned long addr; unsigned int size; } ;

/* Variables and functions */
 TYPE_2__ boot_mem_map ; 

__attribute__((used)) static int addr_is_ram(unsigned long addr, unsigned sz)
{
	int i;

	for (i = 0; i < boot_mem_map.nr_map; i++) {
		unsigned long a = boot_mem_map.map[i].addr;
		if (a <= addr && addr+sz <= a+boot_mem_map.map[i].size)
			return 1;
	}
	return 0;
}