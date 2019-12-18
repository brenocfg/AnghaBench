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
struct ubi_device {int ubi_num; int /*<<< orphan*/  dev; TYPE_1__* mtd; int /*<<< orphan*/  fm_buf; int /*<<< orphan*/  peb_buf; int /*<<< orphan*/  vtbl; int /*<<< orphan*/  fm_work; scalar_t__ bgt_thread; scalar_t__ ref_count; int /*<<< orphan*/  ubi_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int UBI_MAX_DEVICES ; 
 int /*<<< orphan*/  UBI_VOLUME_REMOVED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_mtd_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_dbg_chk_fastmap (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_debugfs_exit_dev (struct ubi_device*) ; 
 int /*<<< orphan*/ ** ubi_devices ; 
 int /*<<< orphan*/  ubi_devices_lock ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ubi_free_internal_volumes (struct ubi_device*) ; 
 struct ubi_device* ubi_get_device (int) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_notify_all (struct ubi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_update_fastmap (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_wl_close (struct ubi_device*) ; 
 int /*<<< orphan*/  uif_close (struct ubi_device*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int ubi_detach_mtd_dev(int ubi_num, int anyway)
{
	struct ubi_device *ubi;

	if (ubi_num < 0 || ubi_num >= UBI_MAX_DEVICES)
		return -EINVAL;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		return -EINVAL;

	spin_lock(&ubi_devices_lock);
	put_device(&ubi->dev);
	ubi->ref_count -= 1;
	if (ubi->ref_count) {
		if (!anyway) {
			spin_unlock(&ubi_devices_lock);
			return -EBUSY;
		}
		/* This may only happen if there is a bug */
		ubi_err(ubi, "%s reference count %d, destroy anyway",
			ubi->ubi_name, ubi->ref_count);
	}
	ubi_devices[ubi_num] = NULL;
	spin_unlock(&ubi_devices_lock);

	ubi_assert(ubi_num == ubi->ubi_num);
	ubi_notify_all(ubi, UBI_VOLUME_REMOVED, NULL);
	ubi_msg(ubi, "detaching mtd%d", ubi->mtd->index);
#ifdef CONFIG_MTD_UBI_FASTMAP
	/* If we don't write a new fastmap at detach time we lose all
	 * EC updates that have been made since the last written fastmap.
	 * In case of fastmap debugging we omit the update to simulate an
	 * unclean shutdown. */
	if (!ubi_dbg_chk_fastmap(ubi))
		ubi_update_fastmap(ubi);
#endif
	/*
	 * Before freeing anything, we have to stop the background thread to
	 * prevent it from doing anything on this device while we are freeing.
	 */
	if (ubi->bgt_thread)
		kthread_stop(ubi->bgt_thread);

#ifdef CONFIG_MTD_UBI_FASTMAP
	cancel_work_sync(&ubi->fm_work);
#endif
	ubi_debugfs_exit_dev(ubi);
	uif_close(ubi);

	ubi_wl_close(ubi);
	ubi_free_internal_volumes(ubi);
	vfree(ubi->vtbl);
	vfree(ubi->peb_buf);
	vfree(ubi->fm_buf);
	ubi_msg(ubi, "mtd%d is detached", ubi->mtd->index);
	put_mtd_device(ubi->mtd);
	put_device(&ubi->dev);
	return 0;
}