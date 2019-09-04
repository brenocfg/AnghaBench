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
struct tsb {int tag; } ;

/* Variables and functions */
 unsigned long KERNEL_TSB_NENTRIES ; 
 unsigned long TSB_TAG_INVALID_BIT ; 
 struct tsb* swapper_tsb ; 

__attribute__((used)) static void flush_tsb_kernel_range_scan(unsigned long start, unsigned long end)
{
	unsigned long idx;

	for (idx = 0; idx < KERNEL_TSB_NENTRIES; idx++) {
		struct tsb *ent = &swapper_tsb[idx];
		unsigned long match = idx << 13;

		match |= (ent->tag << 22);
		if (match >= start && match < end)
			ent->tag = (1UL << TSB_TAG_INVALID_BIT);
	}
}