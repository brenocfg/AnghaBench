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
struct slice_mask {unsigned long low_slices; int /*<<< orphan*/  high_slices; } ;
struct TYPE_2__ {unsigned int user_psize; unsigned char* low_slices_psize; unsigned char* high_slices_psize; int /*<<< orphan*/  slb_addr_limit; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAP_WINDOW ; 
 int SLICE_NUM_HIGH ; 
 int SLICE_NUM_LOW ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned int,int) ; 
 unsigned int mmu_virtual_psize ; 
 int /*<<< orphan*/  slice_dbg (char*,struct mm_struct*) ; 
 struct slice_mask* slice_mask_for_size (struct mm_struct*,unsigned int) ; 

void slice_init_new_context_exec(struct mm_struct *mm)
{
	unsigned char *hpsizes, *lpsizes;
	struct slice_mask *mask;
	unsigned int psize = mmu_virtual_psize;

	slice_dbg("slice_init_new_context_exec(mm=%p)\n", mm);

	/*
	 * In the case of exec, use the default limit. In the
	 * case of fork it is just inherited from the mm being
	 * duplicated.
	 */
#ifdef CONFIG_PPC64
	mm->context.slb_addr_limit = DEFAULT_MAP_WINDOW_USER64;
#else
	mm->context.slb_addr_limit = DEFAULT_MAP_WINDOW;
#endif

	mm->context.user_psize = psize;

	/*
	 * Set all slice psizes to the default.
	 */
	lpsizes = mm->context.low_slices_psize;
	memset(lpsizes, (psize << 4) | psize, SLICE_NUM_LOW >> 1);

	hpsizes = mm->context.high_slices_psize;
	memset(hpsizes, (psize << 4) | psize, SLICE_NUM_HIGH >> 1);

	/*
	 * Slice mask cache starts zeroed, fill the default size cache.
	 */
	mask = slice_mask_for_size(mm, psize);
	mask->low_slices = ~0UL;
	if (SLICE_NUM_HIGH)
		bitmap_fill(mask->high_slices, SLICE_NUM_HIGH);
}