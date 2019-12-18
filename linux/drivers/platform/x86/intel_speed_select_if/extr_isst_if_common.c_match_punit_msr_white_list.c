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
 int ARRAY_SIZE (int*) ; 
 int* punit_msr_white_list ; 

__attribute__((used)) static bool match_punit_msr_white_list(int msr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(punit_msr_white_list); ++i) {
		if (punit_msr_white_list[i] == msr)
			return true;
	}

	return false;
}