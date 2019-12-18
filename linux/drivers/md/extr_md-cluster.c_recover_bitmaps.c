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
typedef  int /*<<< orphan*/  u64 ;
struct mddev {scalar_t__ reshape_position; scalar_t__ recovery_cp; int /*<<< orphan*/  thread; scalar_t__ recovery; int /*<<< orphan*/  sync_thread; struct md_cluster_info* cluster_info; } ;
struct md_thread {struct mddev* mddev; } ;
struct md_cluster_info {int suspend_from; scalar_t__ recovery_map; int /*<<< orphan*/  suspend_lock; scalar_t__ suspend_lo; scalar_t__ suspend_hi; } ;
struct dlm_lock_resource {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_PW ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int MD_RECOVERY_RESHAPE ; 
 int MD_RESYNCING_REMOTE ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  clear_bit (int,scalar_t__*) ; 
 int dlm_lock_sync_interruptible (struct dlm_lock_resource*,int /*<<< orphan*/ ,struct mddev*) ; 
 int fls64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockres_free (struct dlm_lock_resource*) ; 
 struct dlm_lock_resource* lockres_init (struct mddev*,char*,int /*<<< orphan*/ *,int) ; 
 int md_bitmap_copy_from_slot (struct mddev*,int,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,scalar_t__*) ; 

__attribute__((used)) static void recover_bitmaps(struct md_thread *thread)
{
	struct mddev *mddev = thread->mddev;
	struct md_cluster_info *cinfo = mddev->cluster_info;
	struct dlm_lock_resource *bm_lockres;
	char str[64];
	int slot, ret;
	sector_t lo, hi;

	while (cinfo->recovery_map) {
		slot = fls64((u64)cinfo->recovery_map) - 1;

		snprintf(str, 64, "bitmap%04d", slot);
		bm_lockres = lockres_init(mddev, str, NULL, 1);
		if (!bm_lockres) {
			pr_err("md-cluster: Cannot initialize bitmaps\n");
			goto clear_bit;
		}

		ret = dlm_lock_sync_interruptible(bm_lockres, DLM_LOCK_PW, mddev);
		if (ret) {
			pr_err("md-cluster: Could not DLM lock %s: %d\n",
					str, ret);
			goto clear_bit;
		}
		ret = md_bitmap_copy_from_slot(mddev, slot, &lo, &hi, true);
		if (ret) {
			pr_err("md-cluster: Could not copy data from bitmap %d\n", slot);
			goto clear_bit;
		}

		/* Clear suspend_area associated with the bitmap */
		spin_lock_irq(&cinfo->suspend_lock);
		cinfo->suspend_hi = 0;
		cinfo->suspend_lo = 0;
		cinfo->suspend_from = -1;
		spin_unlock_irq(&cinfo->suspend_lock);

		/* Kick off a reshape if needed */
		if (test_bit(MD_RESYNCING_REMOTE, &mddev->recovery) &&
		    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
		    mddev->reshape_position != MaxSector)
			md_wakeup_thread(mddev->sync_thread);

		if (hi > 0) {
			if (lo < mddev->recovery_cp)
				mddev->recovery_cp = lo;
			/* wake up thread to continue resync in case resync
			 * is not finished */
			if (mddev->recovery_cp != MaxSector) {
				/*
				 * clear the REMOTE flag since we will launch
				 * resync thread in current node.
				 */
				clear_bit(MD_RESYNCING_REMOTE,
					  &mddev->recovery);
				set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
				md_wakeup_thread(mddev->thread);
			}
		}
clear_bit:
		lockres_free(bm_lockres);
		clear_bit(slot, &cinfo->recovery_map);
	}
}