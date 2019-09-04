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
struct mddev {scalar_t__ raid_disks; int /*<<< orphan*/  gendisk; int /*<<< orphan*/  array_sectors; int /*<<< orphan*/  private; int /*<<< orphan*/  reconfig_mutex; } ;
struct md_rdev {scalar_t__ saved_raid_disk; scalar_t__ raid_disk; } ;
struct linear_conf {scalar_t__ raid_disks; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  kfree_rcu (struct linear_conf*,int /*<<< orphan*/ ) ; 
 struct linear_conf* linear_conf (struct mddev*,scalar_t__) ; 
 int /*<<< orphan*/  linear_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_set_array_sectors (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mddev_resume (struct mddev*) ; 
 int /*<<< orphan*/  mddev_suspend (struct mddev*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct linear_conf*) ; 
 struct linear_conf* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int linear_add(struct mddev *mddev, struct md_rdev *rdev)
{
	/* Adding a drive to a linear array allows the array to grow.
	 * It is permitted if the new drive has a matching superblock
	 * already on it, with raid_disk equal to raid_disks.
	 * It is achieved by creating a new linear_private_data structure
	 * and swapping it in in-place of the current one.
	 * The current one is never freed until the array is stopped.
	 * This avoids races.
	 */
	struct linear_conf *newconf, *oldconf;

	if (rdev->saved_raid_disk != mddev->raid_disks)
		return -EINVAL;

	rdev->raid_disk = rdev->saved_raid_disk;
	rdev->saved_raid_disk = -1;

	newconf = linear_conf(mddev,mddev->raid_disks+1);

	if (!newconf)
		return -ENOMEM;

	/* newconf->raid_disks already keeps a copy of * the increased
	 * value of mddev->raid_disks, WARN_ONCE() is just used to make
	 * sure of this. It is possible that oldconf is still referenced
	 * in linear_congested(), therefore kfree_rcu() is used to free
	 * oldconf until no one uses it anymore.
	 */
	mddev_suspend(mddev);
	oldconf = rcu_dereference_protected(mddev->private,
			lockdep_is_held(&mddev->reconfig_mutex));
	mddev->raid_disks++;
	WARN_ONCE(mddev->raid_disks != newconf->raid_disks,
		"copied raid_disks doesn't match mddev->raid_disks");
	rcu_assign_pointer(mddev->private, newconf);
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));
	set_capacity(mddev->gendisk, mddev->array_sectors);
	mddev_resume(mddev);
	revalidate_disk(mddev->gendisk);
	kfree_rcu(oldconf, rcu);
	return 0;
}