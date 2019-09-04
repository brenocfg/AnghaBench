#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {unsigned long (* get_unmapped_area ) (struct file*,unsigned long,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 TYPE_2__* current ; 

unsigned long get_fb_unmapped_area(struct file *filp, unsigned long orig_addr, unsigned long len, unsigned long pgoff, unsigned long flags)
{
	unsigned long align_goal, addr = -ENOMEM;
	unsigned long (*get_area)(struct file *, unsigned long,
				  unsigned long, unsigned long, unsigned long);

	get_area = current->mm->get_unmapped_area;

	if (flags & MAP_FIXED) {
		/* Ok, don't mess with it. */
		return get_area(NULL, orig_addr, len, pgoff, flags);
	}
	flags &= ~MAP_SHARED;

	align_goal = PAGE_SIZE;
	if (len >= (4UL * 1024 * 1024))
		align_goal = (4UL * 1024 * 1024);
	else if (len >= (512UL * 1024))
		align_goal = (512UL * 1024);
	else if (len >= (64UL * 1024))
		align_goal = (64UL * 1024);

	do {
		addr = get_area(NULL, orig_addr, len + (align_goal - PAGE_SIZE), pgoff, flags);
		if (!(addr & ~PAGE_MASK)) {
			addr = (addr + (align_goal - 1UL)) & ~(align_goal - 1UL);
			break;
		}

		if (align_goal == (4UL * 1024 * 1024))
			align_goal = (512UL * 1024);
		else if (align_goal == (512UL * 1024))
			align_goal = (64UL * 1024);
		else
			align_goal = PAGE_SIZE;
	} while ((addr & ~PAGE_MASK) && align_goal > PAGE_SIZE);

	/* Mapping is smaller than 64K or larger areas could not
	 * be obtained.
	 */
	if (addr & ~PAGE_MASK)
		addr = get_area(NULL, orig_addr, len, pgoff, flags);

	return addr;
}