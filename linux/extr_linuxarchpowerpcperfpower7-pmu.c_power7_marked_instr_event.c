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
 int PM_PMCSEL_MSK ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_UNIT_MSK ; 
 int PM_UNIT_SH ; 

__attribute__((used)) static int power7_marked_instr_event(u64 event)
{
	int pmc, psel;
	int unit;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	psel = event & PM_PMCSEL_MSK & ~1;	/* trim off edge/level bit */
	if (pmc >= 5)
		return 0;

	switch (psel >> 4) {
	case 2:
		return pmc == 2 || pmc == 4;
	case 3:
		if (psel == 0x3c)
			return pmc == 1;
		if (psel == 0x3e)
			return pmc != 2;
		return 1;
	case 4:
	case 5:
		return unit == 0xd;
	case 6:
		if (psel == 0x64)
			return pmc >= 3;
	case 8:
		return unit == 0xd;
	}
	return 0;
}