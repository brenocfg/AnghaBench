#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* low_slices_psize; unsigned char* high_slices_psize; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int GET_HIGH_SLICE_INDEX (unsigned long) ; 
 int GET_LOW_SLICE_INDEX (unsigned long) ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 scalar_t__ slice_addr_is_low (unsigned long) ; 

unsigned int get_slice_psize(struct mm_struct *mm, unsigned long addr)
{
	unsigned char *psizes;
	int index, mask_index;

	VM_BUG_ON(radix_enabled());

	if (slice_addr_is_low(addr)) {
		psizes = mm->context.low_slices_psize;
		index = GET_LOW_SLICE_INDEX(addr);
	} else {
		psizes = mm->context.high_slices_psize;
		index = GET_HIGH_SLICE_INDEX(addr);
	}
	mask_index = index & 0x1;
	return (psizes[index >> 1] >> (mask_index * 4)) & 0xf;
}