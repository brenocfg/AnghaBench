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
struct gmap {TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 int __gmap_link (struct gmap*,unsigned long,unsigned long) ; 
 unsigned long __gmap_translate (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fixup_user_fault (int /*<<< orphan*/ ,TYPE_1__*,unsigned long,unsigned int,int*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int gmap_fault(struct gmap *gmap, unsigned long gaddr,
	       unsigned int fault_flags)
{
	unsigned long vmaddr;
	int rc;
	bool unlocked;

	down_read(&gmap->mm->mmap_sem);

retry:
	unlocked = false;
	vmaddr = __gmap_translate(gmap, gaddr);
	if (IS_ERR_VALUE(vmaddr)) {
		rc = vmaddr;
		goto out_up;
	}
	if (fixup_user_fault(current, gmap->mm, vmaddr, fault_flags,
			     &unlocked)) {
		rc = -EFAULT;
		goto out_up;
	}
	/*
	 * In the case that fixup_user_fault unlocked the mmap_sem during
	 * faultin redo __gmap_translate to not race with a map/unmap_segment.
	 */
	if (unlocked)
		goto retry;

	rc = __gmap_link(gmap, gaddr, vmaddr);
out_up:
	up_read(&gmap->mm->mmap_sem);
	return rc;
}