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
 int SLB_VSID_B_1T ; 

__attribute__((used)) static u64 next_segment(u64 ea, u64 vsid)
{
	if (vsid & SLB_VSID_B_1T)
		ea |= (1ULL << 40) - 1;
	else
		ea |= (1ULL << 28) - 1;

	return ea + 1;
}