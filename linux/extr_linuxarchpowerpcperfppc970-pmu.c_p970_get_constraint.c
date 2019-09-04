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
typedef  int u64 ;

/* Variables and functions */
 int PM_BYTE_MSK ; 
 int PM_BYTE_SH ; 
 int PM_LASTUNIT ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_SPCSEL_MSK ; 
 int PM_SPCSEL_SH ; 
 int PM_UNIT_MSK ; 
 int PM_UNIT_SH ; 
 unsigned long** unit_cons ; 

__attribute__((used)) static int p970_get_constraint(u64 event, unsigned long *maskp,
			       unsigned long *valp)
{
	int pmc, byte, unit, sh, spcsel;
	unsigned long mask = 0, value = 0;
	int grp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 8)
			return -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		grp = ((pmc - 1) >> 1) & 1;
	}
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	if (unit) {
		if (unit > PM_LASTUNIT)
			return -1;
		mask |= unit_cons[unit][0];
		value |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2/5/6; bytes 1 and 3 on PMC3/4/7/8.
		 */
		if (!pmc)
			grp = byte & 1;
		/* Set byte lane select field */
		mask  |= 0xfULL << (28 - 4 * byte);
		value |= (unsigned long)unit << (28 - 4 * byte);
	}
	if (grp == 0) {
		/* increment PMC1/2/5/6 field */
		mask  |= 0x8000000000ull;
		value |= 0x1000000000ull;
	} else if (grp == 1) {
		/* increment PMC3/4/7/8 field */
		mask  |= 0x800000000ull;
		value |= 0x100000000ull;
	}
	spcsel = (event >> PM_SPCSEL_SH) & PM_SPCSEL_MSK;
	if (spcsel) {
		mask  |= 3ull << 48;
		value |= (unsigned long)spcsel << 48;
	}
	*maskp = mask;
	*valp = value;
	return 0;
}