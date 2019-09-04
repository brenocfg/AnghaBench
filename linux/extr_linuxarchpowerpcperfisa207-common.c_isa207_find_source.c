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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HIT ; 
 int /*<<< orphan*/  HITM ; 
 int /*<<< orphan*/  L1 ; 
 int /*<<< orphan*/  L2 ; 
 int /*<<< orphan*/  L3 ; 
 int /*<<< orphan*/  LOC_RAM ; 
 int /*<<< orphan*/  LVL ; 
 int P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PERF_MEM_NA ; 
 int PH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REM_CCE1 ; 
 int /*<<< orphan*/  REM_CCE2 ; 
 int /*<<< orphan*/  REM_RAM1 ; 
 int /*<<< orphan*/  REM_RAM2 ; 
 int /*<<< orphan*/  SNOOP ; 

__attribute__((used)) static inline u64 isa207_find_source(u64 idx, u32 sub_idx)
{
	u64 ret = PERF_MEM_NA;

	switch(idx) {
	case 0:
		/* Nothing to do */
		break;
	case 1:
		ret = PH(LVL, L1);
		break;
	case 2:
		ret = PH(LVL, L2);
		break;
	case 3:
		ret = PH(LVL, L3);
		break;
	case 4:
		if (sub_idx <= 1)
			ret = PH(LVL, LOC_RAM);
		else if (sub_idx > 1 && sub_idx <= 2)
			ret = PH(LVL, REM_RAM1);
		else
			ret = PH(LVL, REM_RAM2);
		ret |= P(SNOOP, HIT);
		break;
	case 5:
		ret = PH(LVL, REM_CCE1);
		if ((sub_idx == 0) || (sub_idx == 2) || (sub_idx == 4))
			ret |= P(SNOOP, HIT);
		else if ((sub_idx == 1) || (sub_idx == 3) || (sub_idx == 5))
			ret |= P(SNOOP, HITM);
		break;
	case 6:
		ret = PH(LVL, REM_CCE2);
		if ((sub_idx == 0) || (sub_idx == 2))
			ret |= P(SNOOP, HIT);
		else if ((sub_idx == 1) || (sub_idx == 3))
			ret |= P(SNOOP, HITM);
		break;
	case 7:
		ret = PM(LVL, L1);
		break;
	}

	return ret;
}