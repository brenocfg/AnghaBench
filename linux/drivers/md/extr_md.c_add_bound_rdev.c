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
struct mddev {size_t major_version; int /*<<< orphan*/  thread; int /*<<< orphan*/  recovery; scalar_t__ degraded; int /*<<< orphan*/  sb_flags; TYPE_1__* pers; } ;
struct md_rdev {int /*<<< orphan*/  sysfs_state; int /*<<< orphan*/  flags; struct mddev* mddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* validate_super ) (struct mddev*,struct md_rdev*) ;} ;
struct TYPE_3__ {int (* hot_add_disk ) (struct mddev*,struct md_rdev*) ;int /*<<< orphan*/  hot_remove_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  Journal ; 
 int /*<<< orphan*/  MD_RECOVERY_NEEDED ; 
 int /*<<< orphan*/  MD_RECOVERY_RECOVER ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  md_kick_rdev_from_array (struct md_rdev*) ; 
 int /*<<< orphan*/  md_new_event (struct mddev*) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct md_rdev*) ; 
 int stub2 (struct mddev*,struct md_rdev*) ; 
 TYPE_2__* super_types ; 
 int /*<<< orphan*/  sysfs_notify_dirent_safe (int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_bound_rdev(struct md_rdev *rdev)
{
	struct mddev *mddev = rdev->mddev;
	int err = 0;
	bool add_journal = test_bit(Journal, &rdev->flags);

	if (!mddev->pers->hot_remove_disk || add_journal) {
		/* If there is hot_add_disk but no hot_remove_disk
		 * then added disks for geometry changes,
		 * and should be added immediately.
		 */
		super_types[mddev->major_version].
			validate_super(mddev, rdev);
		if (add_journal)
			mddev_suspend(mddev);
		err = mddev->pers->hot_add_disk(mddev, rdev);
		if (add_journal)
			mddev_resume(mddev);
		if (err) {
			md_kick_rdev_from_array(rdev);
			return err;
		}
	}
	sysfs_notify_dirent_safe(rdev->sysfs_state);

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	if (mddev->degraded)
		set_bit(MD_RECOVERY_RECOVER, &mddev->recovery);
	set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
	md_new_event(mddev);
	md_wakeup_thread(mddev->thread);
	return 0;
}