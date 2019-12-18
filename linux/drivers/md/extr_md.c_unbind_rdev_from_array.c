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
struct TYPE_3__ {scalar_t__ count; } ;
struct md_rdev {int /*<<< orphan*/  del_work; int /*<<< orphan*/  kobj; TYPE_1__ badblocks; int /*<<< orphan*/ * sysfs_state; TYPE_2__* mddev; int /*<<< orphan*/  bdev; int /*<<< orphan*/  same_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  gendisk; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_unlink_disk_holder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_delayed_delete ; 
 int /*<<< orphan*/  md_misc_wq ; 
 int /*<<< orphan*/  mddev_destroy_wb_pool (TYPE_2__*,struct md_rdev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  sysfs_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void unbind_rdev_from_array(struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];

	bd_unlink_disk_holder(rdev->bdev, rdev->mddev->gendisk);
	list_del_rcu(&rdev->same_set);
	pr_debug("md: unbind<%s>\n", bdevname(rdev->bdev,b));
	mddev_destroy_wb_pool(rdev->mddev, rdev);
	rdev->mddev = NULL;
	sysfs_remove_link(&rdev->kobj, "block");
	sysfs_put(rdev->sysfs_state);
	rdev->sysfs_state = NULL;
	rdev->badblocks.count = 0;
	/* We need to delay this, otherwise we can deadlock when
	 * writing to 'remove' to "dev/state".  We also need
	 * to delay it due to rcu usage.
	 */
	synchronize_rcu();
	INIT_WORK(&rdev->del_work, md_delayed_delete);
	kobject_get(&rdev->kobj);
	queue_work(md_misc_wq, &rdev->del_work);
}