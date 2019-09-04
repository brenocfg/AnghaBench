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
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  physmem; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 TYPE_1__ memblock ; 
 int /*<<< orphan*/  memblock_add_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memblock_dbg (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void memblock_physmem_add(phys_addr_t start, phys_addr_t size)
{
	memblock_dbg("memblock_physmem_add: [%#016llx-%#016llx]\n",
		     start, start + size - 1);
	memblock_add_range(&memblock.memory, start, size, 0, 0);
	memblock_add_range(&memblock.physmem, start, size, 0, 0);
}