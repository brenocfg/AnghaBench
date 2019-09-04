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
struct hd_struct {scalar_t__ partno; } ;
struct gendisk {scalar_t__ minors; scalar_t__ first_minor; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_EXT_MAJOR ; 
 int EBUSY ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NR_EXT_DEVT ; 
 scalar_t__ blk_mangle_minor (int) ; 
 int /*<<< orphan*/  ext_devt_idr ; 
 int /*<<< orphan*/  ext_devt_lock ; 
 int idr_alloc (int /*<<< orphan*/ *,struct hd_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 struct gendisk* part_to_disk (struct hd_struct*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int blk_alloc_devt(struct hd_struct *part, dev_t *devt)
{
	struct gendisk *disk = part_to_disk(part);
	int idx;

	/* in consecutive minor range? */
	if (part->partno < disk->minors) {
		*devt = MKDEV(disk->major, disk->first_minor + part->partno);
		return 0;
	}

	/* allocate ext devt */
	idr_preload(GFP_KERNEL);

	spin_lock_bh(&ext_devt_lock);
	idx = idr_alloc(&ext_devt_idr, part, 0, NR_EXT_DEVT, GFP_NOWAIT);
	spin_unlock_bh(&ext_devt_lock);

	idr_preload_end();
	if (idx < 0)
		return idx == -ENOSPC ? -EBUSY : idx;

	*devt = MKDEV(BLOCK_EXT_MAJOR, blk_mangle_minor(idx));
	return 0;
}