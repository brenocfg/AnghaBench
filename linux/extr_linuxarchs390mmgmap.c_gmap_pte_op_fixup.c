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
struct mm_struct {int dummy; } ;
struct gmap {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 unsigned int FAULT_FLAG_WRITE ; 
 int PROT_WRITE ; 
 int __gmap_link (struct gmap*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fixup_user_fault (int /*<<< orphan*/ ,struct mm_struct*,unsigned long,unsigned int,int*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 

__attribute__((used)) static int gmap_pte_op_fixup(struct gmap *gmap, unsigned long gaddr,
			     unsigned long vmaddr, int prot)
{
	struct mm_struct *mm = gmap->mm;
	unsigned int fault_flags;
	bool unlocked = false;

	BUG_ON(gmap_is_shadow(gmap));
	fault_flags = (prot == PROT_WRITE) ? FAULT_FLAG_WRITE : 0;
	if (fixup_user_fault(current, mm, vmaddr, fault_flags, &unlocked))
		return -EFAULT;
	if (unlocked)
		/* lost mmap_sem, caller has to retry __gmap_translate */
		return 0;
	/* Connect the page tables */
	return __gmap_link(gmap, gaddr, vmaddr);
}