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
 int MBM_CNTR_WIDTH ; 

__attribute__((used)) static u64 mbm_overflow_count(u64 prev_msr, u64 cur_msr)
{
	u64 shift = 64 - MBM_CNTR_WIDTH, chunks;

	chunks = (cur_msr << shift) - (prev_msr << shift);
	return chunks >>= shift;
}