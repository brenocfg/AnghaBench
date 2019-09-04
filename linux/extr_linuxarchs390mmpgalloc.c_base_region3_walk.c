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

/* Variables and functions */
 int ENOMEM ; 
 unsigned long _REGION3_ENTRY ; 
 unsigned long _REGION3_INDEX ; 
 unsigned long _REGION3_SHIFT ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 int /*<<< orphan*/  _SEGMENT_ENTRY_EMPTY ; 
 unsigned long base_crst_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_crst_free (unsigned long) ; 
 unsigned long base_region3_addr_end (unsigned long,unsigned long) ; 
 int base_segment_walk (unsigned long,unsigned long,unsigned long,int) ; 

__attribute__((used)) static int base_region3_walk(unsigned long origin, unsigned long addr,
			     unsigned long end, int alloc)
{
	unsigned long *rtte, next, table;
	int rc;

	rtte = (unsigned long *) origin;
	rtte += (addr & _REGION3_INDEX) >> _REGION3_SHIFT;
	do {
		next = base_region3_addr_end(addr, end);
		if (*rtte & _REGION_ENTRY_INVALID) {
			if (!alloc)
				continue;
			table = base_crst_alloc(_SEGMENT_ENTRY_EMPTY);
			if (!table)
				return -ENOMEM;
			*rtte = table | _REGION3_ENTRY;
		}
		table = *rtte & _REGION_ENTRY_ORIGIN;
		rc = base_segment_walk(table, addr, next, alloc);
		if (rc)
			return rc;
		if (!alloc)
			base_crst_free(table);
	} while (rtte++, addr = next, addr < end);
	return 0;
}