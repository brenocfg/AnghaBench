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
 unsigned long _ASCE_ORIGIN ; 
 unsigned long _ASCE_TYPE_MASK ; 
#define  _ASCE_TYPE_REGION1 131 
#define  _ASCE_TYPE_REGION2 130 
#define  _ASCE_TYPE_REGION3 129 
#define  _ASCE_TYPE_SEGMENT 128 
 unsigned long _PAGE_INDEX ; 
 unsigned long _PAGE_SHIFT ; 
 unsigned long _REGION1_INDEX ; 
 unsigned long _REGION1_SHIFT ; 
 unsigned long _REGION2_INDEX ; 
 unsigned long _REGION2_SHIFT ; 
 unsigned long _REGION3_ENTRY_LARGE ; 
 unsigned long _REGION3_INDEX ; 
 unsigned long _REGION3_SHIFT ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 unsigned long _SEGMENT_ENTRY_LARGE ; 
 unsigned long _SEGMENT_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_INDEX ; 
 unsigned long _SEGMENT_SHIFT ; 
 unsigned long* __va (unsigned long) ; 
 scalar_t__ bad_address (unsigned long*) ; 
 int /*<<< orphan*/  pr_alert (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void dump_pagetable(unsigned long asce, unsigned long address)
{
	unsigned long *table = __va(asce & _ASCE_ORIGIN);

	pr_alert("AS:%016lx ", asce);
	switch (asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_REGION1:
		table += (address & _REGION1_INDEX) >> _REGION1_SHIFT;
		if (bad_address(table))
			goto bad;
		pr_cont("R1:%016lx ", *table);
		if (*table & _REGION_ENTRY_INVALID)
			goto out;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* fallthrough */
	case _ASCE_TYPE_REGION2:
		table += (address & _REGION2_INDEX) >> _REGION2_SHIFT;
		if (bad_address(table))
			goto bad;
		pr_cont("R2:%016lx ", *table);
		if (*table & _REGION_ENTRY_INVALID)
			goto out;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* fallthrough */
	case _ASCE_TYPE_REGION3:
		table += (address & _REGION3_INDEX) >> _REGION3_SHIFT;
		if (bad_address(table))
			goto bad;
		pr_cont("R3:%016lx ", *table);
		if (*table & (_REGION_ENTRY_INVALID | _REGION3_ENTRY_LARGE))
			goto out;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
		/* fallthrough */
	case _ASCE_TYPE_SEGMENT:
		table += (address & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
		if (bad_address(table))
			goto bad;
		pr_cont("S:%016lx ", *table);
		if (*table & (_SEGMENT_ENTRY_INVALID | _SEGMENT_ENTRY_LARGE))
			goto out;
		table = (unsigned long *)(*table & _SEGMENT_ENTRY_ORIGIN);
	}
	table += (address & _PAGE_INDEX) >> _PAGE_SHIFT;
	if (bad_address(table))
		goto bad;
	pr_cont("P:%016lx ", *table);
out:
	pr_cont("\n");
	return;
bad:
	pr_cont("BAD\n");
}