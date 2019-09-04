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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long HV_TLB_FLUSH_UNIT ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static inline int fill_gva_list(u64 gva_list[], int offset,
				unsigned long start, unsigned long end)
{
	int gva_n = offset;
	unsigned long cur = start, diff;

	do {
		diff = end > cur ? end - cur : 0;

		gva_list[gva_n] = cur & PAGE_MASK;
		/*
		 * Lower 12 bits encode the number of additional
		 * pages to flush (in addition to the 'cur' page).
		 */
		if (diff >= HV_TLB_FLUSH_UNIT)
			gva_list[gva_n] |= ~PAGE_MASK;
		else if (diff)
			gva_list[gva_n] |= (diff - 1) >> PAGE_SHIFT;

		cur += HV_TLB_FLUSH_UNIT;
		gva_n++;

	} while (cur < end);

	return gva_n - offset;
}