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
struct gmap {unsigned long asce_end; TYPE_1__* mm; int /*<<< orphan*/  guest_to_host; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned long PMD_SHIFT ; 
 int PMD_SIZE ; 
 unsigned long TASK_SIZE_MAX ; 
 int __gmap_unmap_by_gaddr (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gmap_flush_tlb (struct gmap*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  gmap_unmap_segment (struct gmap*,unsigned long,unsigned long) ; 
 scalar_t__ radix_tree_insert (int /*<<< orphan*/ *,unsigned long,void*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int gmap_map_segment(struct gmap *gmap, unsigned long from,
		     unsigned long to, unsigned long len)
{
	unsigned long off;
	int flush;

	BUG_ON(gmap_is_shadow(gmap));
	if ((from | to | len) & (PMD_SIZE - 1))
		return -EINVAL;
	if (len == 0 || from + len < from || to + len < to ||
	    from + len - 1 > TASK_SIZE_MAX || to + len - 1 > gmap->asce_end)
		return -EINVAL;

	flush = 0;
	down_write(&gmap->mm->mmap_sem);
	for (off = 0; off < len; off += PMD_SIZE) {
		/* Remove old translation */
		flush |= __gmap_unmap_by_gaddr(gmap, to + off);
		/* Store new translation */
		if (radix_tree_insert(&gmap->guest_to_host,
				      (to + off) >> PMD_SHIFT,
				      (void *) from + off))
			break;
	}
	up_write(&gmap->mm->mmap_sem);
	if (flush)
		gmap_flush_tlb(gmap);
	if (off >= len)
		return 0;
	gmap_unmap_segment(gmap, to, len);
	return -ENOMEM;
}