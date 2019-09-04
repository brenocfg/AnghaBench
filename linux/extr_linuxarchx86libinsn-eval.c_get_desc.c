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
struct desc_struct {int dummy; } ;
struct desc_ptr {unsigned long size; scalar_t__ address; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 unsigned short SEGMENT_RPL_MASK ; 
 unsigned short SEGMENT_TI_MASK ; 
 int /*<<< orphan*/  native_store_gdt (struct desc_ptr*) ; 

__attribute__((used)) static struct desc_struct *get_desc(unsigned short sel)
{
	struct desc_ptr gdt_desc = {0, 0};
	unsigned long desc_base;

#ifdef CONFIG_MODIFY_LDT_SYSCALL
	if ((sel & SEGMENT_TI_MASK) == SEGMENT_LDT) {
		struct desc_struct *desc = NULL;
		struct ldt_struct *ldt;

		/* Bits [15:3] contain the index of the desired entry. */
		sel >>= 3;

		mutex_lock(&current->active_mm->context.lock);
		ldt = current->active_mm->context.ldt;
		if (ldt && sel < ldt->nr_entries)
			desc = &ldt->entries[sel];

		mutex_unlock(&current->active_mm->context.lock);

		return desc;
	}
#endif
	native_store_gdt(&gdt_desc);

	/*
	 * Segment descriptors have a size of 8 bytes. Thus, the index is
	 * multiplied by 8 to obtain the memory offset of the desired descriptor
	 * from the base of the GDT. As bits [15:3] of the segment selector
	 * contain the index, it can be regarded as multiplied by 8 already.
	 * All that remains is to clear bits [2:0].
	 */
	desc_base = sel & ~(SEGMENT_RPL_MASK | SEGMENT_TI_MASK);

	if (desc_base > gdt_desc.size)
		return NULL;

	return (struct desc_struct *)(gdt_desc.address + desc_base);
}