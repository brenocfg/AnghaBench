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
struct gendisk {struct disk_events* ev; struct block_device_operations* fops; } ;
struct disk_events {unsigned int clearing; unsigned int pending; int /*<<< orphan*/  lock; } ;
struct block_device_operations {scalar_t__ (* media_changed ) (struct gendisk*) ;} ;

/* Variables and functions */
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (unsigned int) ; 
 int /*<<< orphan*/  __disk_unblock_events (struct gendisk*,int) ; 
 int /*<<< orphan*/  disk_block_events (struct gendisk*) ; 
 int /*<<< orphan*/  disk_check_events (struct disk_events*,unsigned int*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct gendisk*) ; 

unsigned int disk_clear_events(struct gendisk *disk, unsigned int mask)
{
	const struct block_device_operations *bdops = disk->fops;
	struct disk_events *ev = disk->ev;
	unsigned int pending;
	unsigned int clearing = mask;

	if (!ev) {
		/* for drivers still using the old ->media_changed method */
		if ((mask & DISK_EVENT_MEDIA_CHANGE) &&
		    bdops->media_changed && bdops->media_changed(disk))
			return DISK_EVENT_MEDIA_CHANGE;
		return 0;
	}

	disk_block_events(disk);

	/*
	 * store the union of mask and ev->clearing on the stack so that the
	 * race with disk_flush_events does not cause ambiguity (ev->clearing
	 * can still be modified even if events are blocked).
	 */
	spin_lock_irq(&ev->lock);
	clearing |= ev->clearing;
	ev->clearing = 0;
	spin_unlock_irq(&ev->lock);

	disk_check_events(ev, &clearing);
	/*
	 * if ev->clearing is not 0, the disk_flush_events got called in the
	 * middle of this function, so we want to run the workfn without delay.
	 */
	__disk_unblock_events(disk, ev->clearing ? true : false);

	/* then, fetch and clear pending events */
	spin_lock_irq(&ev->lock);
	pending = ev->pending & mask;
	ev->pending &= ~mask;
	spin_unlock_irq(&ev->lock);
	WARN_ON_ONCE(clearing & mask);

	return pending;
}