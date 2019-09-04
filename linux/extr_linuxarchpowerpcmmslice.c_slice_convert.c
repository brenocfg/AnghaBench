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
struct slice_mask {unsigned int low_slices; int /*<<< orphan*/  high_slices; } ;
struct TYPE_2__ {unsigned char* low_slices_psize; unsigned char* high_slices_psize; int /*<<< orphan*/  slb_addr_limit; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 unsigned long GET_HIGH_SLICE_INDEX (int /*<<< orphan*/ ) ; 
 unsigned long SLICE_NUM_LOW ; 
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copro_flush_all_slbs (struct mm_struct*) ; 
 int /*<<< orphan*/  slice_convert_lock ; 
 int /*<<< orphan*/  slice_dbg (char*,...) ; 
 struct slice_mask* slice_mask_for_size (struct mm_struct*,int) ; 
 int /*<<< orphan*/  slice_print_mask (char*,struct slice_mask const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slice_convert(struct mm_struct *mm,
				const struct slice_mask *mask, int psize)
{
	int index, mask_index;
	/* Write the new slice psize bits */
	unsigned char *hpsizes, *lpsizes;
	struct slice_mask *psize_mask, *old_mask;
	unsigned long i, flags;
	int old_psize;

	slice_dbg("slice_convert(mm=%p, psize=%d)\n", mm, psize);
	slice_print_mask(" mask", mask);

	psize_mask = slice_mask_for_size(mm, psize);

	/* We need to use a spinlock here to protect against
	 * concurrent 64k -> 4k demotion ...
	 */
	spin_lock_irqsave(&slice_convert_lock, flags);

	lpsizes = mm->context.low_slices_psize;
	for (i = 0; i < SLICE_NUM_LOW; i++) {
		if (!(mask->low_slices & (1u << i)))
			continue;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the slice_mask */
		old_psize = (lpsizes[index] >> (mask_index * 4)) & 0xf;
		old_mask = slice_mask_for_size(mm, old_psize);
		old_mask->low_slices &= ~(1u << i);
		psize_mask->low_slices |= 1u << i;

		/* Update the sizes array */
		lpsizes[index] = (lpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((unsigned long)psize) << (mask_index * 4));
	}

	hpsizes = mm->context.high_slices_psize;
	for (i = 0; i < GET_HIGH_SLICE_INDEX(mm->context.slb_addr_limit); i++) {
		if (!test_bit(i, mask->high_slices))
			continue;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the slice_mask */
		old_psize = (hpsizes[index] >> (mask_index * 4)) & 0xf;
		old_mask = slice_mask_for_size(mm, old_psize);
		__clear_bit(i, old_mask->high_slices);
		__set_bit(i, psize_mask->high_slices);

		/* Update the sizes array */
		hpsizes[index] = (hpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((unsigned long)psize) << (mask_index * 4));
	}

	slice_dbg(" lsps=%lx, hsps=%lx\n",
		  (unsigned long)mm->context.low_slices_psize,
		  (unsigned long)mm->context.high_slices_psize);

	spin_unlock_irqrestore(&slice_convert_lock, flags);

	copro_flush_all_slbs(mm);
}