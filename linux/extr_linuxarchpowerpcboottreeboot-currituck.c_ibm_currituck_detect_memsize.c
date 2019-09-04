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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ DDR3_MR0CF ; 
 unsigned int MAX_RANKS ; 
 int mfdcrx (scalar_t__) ; 

__attribute__((used)) static unsigned long long ibm_currituck_detect_memsize(void)
{
	u32 reg;
	unsigned i;
	unsigned long long memsize = 0;

	for(i = 0; i < MAX_RANKS; i++){
		reg = mfdcrx(DDR3_MR0CF + i);

		if (!(reg & 1))
			continue;

		reg &= 0x0000f000;
		reg >>= 12;
		memsize += (0x800000ULL << reg);
	}

	return memsize;
}