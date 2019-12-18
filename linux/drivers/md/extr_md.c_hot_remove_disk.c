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
struct mddev {scalar_t__ thread; int /*<<< orphan*/  sb_flags; int /*<<< orphan*/  pers; } ;
struct md_rdev {scalar_t__ raid_disk; int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_disk ) (struct mddev*,struct md_rdev*) ;} ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Blocked ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct md_rdev* find_rdev (struct mddev*,int /*<<< orphan*/ ) ; 
 TYPE_1__* md_cluster_ops ; 
 int /*<<< orphan*/  md_kick_rdev_from_array (struct md_rdev*) ; 
 int /*<<< orphan*/  md_new_event (struct mddev*) ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (scalar_t__) ; 
 scalar_t__ mddev_is_clustered (struct mddev*) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_and_add_spares (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct md_rdev*) ; 

__attribute__((used)) static int hot_remove_disk(struct mddev *mddev, dev_t dev)
{
	char b[BDEVNAME_SIZE];
	struct md_rdev *rdev;

	if (!mddev->pers)
		return -ENODEV;

	rdev = find_rdev(mddev, dev);
	if (!rdev)
		return -ENXIO;

	if (rdev->raid_disk < 0)
		goto kick_rdev;

	clear_bit(Blocked, &rdev->flags);
	remove_and_add_spares(mddev, rdev);

	if (rdev->raid_disk >= 0)
		goto busy;

kick_rdev:
	if (mddev_is_clustered(mddev))
		md_cluster_ops->remove_disk(mddev, rdev);

	md_kick_rdev_from_array(rdev);
	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	if (mddev->thread)
		md_wakeup_thread(mddev->thread);
	else
		md_update_sb(mddev, 1);
	md_new_event(mddev);

	return 0;
busy:
	pr_debug("md: cannot remove active disk %s from %s ...\n",
		 bdevname(rdev->bdev,b), mdname(mddev));
	return -EBUSY;
}