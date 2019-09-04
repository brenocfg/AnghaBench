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
struct suspend_info {int slot; int /*<<< orphan*/  list; void* hi; void* lo; } ;
struct mddev {TYPE_1__* pers; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  suspend_lock; int /*<<< orphan*/  suspend_list; void* sync_hi; void* sync_low; } ;
typedef  void* sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* quiesce ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RESYNCING_REMOTE ; 
 int /*<<< orphan*/  __remove_suspend_info (struct md_cluster_info*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct suspend_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_bitmap_sync_with_cluster (struct mddev*,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_suspend_info (struct mddev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,int) ; 

__attribute__((used)) static void process_suspend_info(struct mddev *mddev,
		int slot, sector_t lo, sector_t hi)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	struct suspend_info *s;

	if (!hi) {
		/*
		 * clear the REMOTE flag since resync or recovery is finished
		 * in remote node.
		 */
		clear_bit(MD_RESYNCING_REMOTE, &mddev->recovery);
		remove_suspend_info(mddev, slot);
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thread(mddev->thread);
		return;
	}

	/*
	 * The bitmaps are not same for different nodes
	 * if RESYNCING is happening in one node, then
	 * the node which received the RESYNCING message
	 * probably will perform resync with the region
	 * [lo, hi] again, so we could reduce resync time
	 * a lot if we can ensure that the bitmaps among
	 * different nodes are match up well.
	 *
	 * sync_low/hi is used to record the region which
	 * arrived in the previous RESYNCING message,
	 *
	 * Call bitmap_sync_with_cluster to clear
	 * NEEDED_MASK and set RESYNC_MASK since
	 * resync thread is running in another node,
	 * so we don't need to do the resync again
	 * with the same section */
	md_bitmap_sync_with_cluster(mddev, cinfo->sync_low, cinfo->sync_hi, lo, hi);
	cinfo->sync_low = lo;
	cinfo->sync_hi = hi;

	s = kzalloc(sizeof(struct suspend_info), GFP_KERNEL);
	if (!s)
		return;
	s->slot = slot;
	s->lo = lo;
	s->hi = hi;
	mddev->pers->quiesce(mddev, 1);
	spin_lock_irq(&cinfo->suspend_lock);
	/* Remove existing entry (if exists) before adding */
	__remove_suspend_info(cinfo, slot);
	list_add(&s->list, &cinfo->suspend_list);
	spin_unlock_irq(&cinfo->suspend_lock);
	mddev->pers->quiesce(mddev, 0);
}