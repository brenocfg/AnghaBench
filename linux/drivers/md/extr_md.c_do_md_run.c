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
struct mddev {int changed; int /*<<< orphan*/  flags; int /*<<< orphan*/  kobj; int /*<<< orphan*/  sysfs_action; int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  gendisk; int /*<<< orphan*/  array_sectors; int /*<<< orphan*/  sync_thread; int /*<<< orphan*/  thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  MD_NOT_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_allow_write (struct mddev*) ; 
 int /*<<< orphan*/  md_bitmap_destroy (struct mddev*) ; 
 int md_bitmap_load (struct mddev*) ; 
 int md_run (struct mddev*) ; 
 int /*<<< orphan*/  md_start (struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_md_run(struct mddev *mddev)
{
	int err;

	set_bit(MD_NOT_READY, &mddev->flags);
	err = md_run(mddev);
	if (err)
		goto out;
	err = md_bitmap_load(mddev);
	if (err) {
		md_bitmap_destroy(mddev);
		goto out;
	}

	if (mddev_is_clustered(mddev))
		md_allow_write(mddev);

	/* run start up tasks that require md_thread */
	md_start(mddev);

	md_wakeup_thread(mddev->thread);
	md_wakeup_thread(mddev->sync_thread); /* possibly kick off a reshape */

	set_capacity(mddev->gendisk, mddev->array_sectors);
	revalidate_disk(mddev->gendisk);
	clear_bit(MD_NOT_READY, &mddev->flags);
	mddev->changed = 1;
	kobject_uevent(&disk_to_dev(mddev->gendisk)->kobj, KOBJ_CHANGE);
	sysfs_notify_dirent_safe(mddev->sysfs_state);
	sysfs_notify_dirent_safe(mddev->sysfs_action);
	sysfs_notify(&mddev->kobj, NULL, "degraded");
out:
	clear_bit(MD_NOT_READY, &mddev->flags);
	return err;
}