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
struct mddev {struct linear_conf* private; int /*<<< orphan*/  raid_disks; } ;
struct linear_conf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kfree (struct linear_conf*) ; 
 struct linear_conf* linear_conf (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_size (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ md_check_no_bitmap (struct mddev*) ; 
 int md_integrity_register (struct mddev*) ; 
 int /*<<< orphan*/  md_set_array_sectors (struct mddev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int linear_run (struct mddev *mddev)
{
	struct linear_conf *conf;
	int ret;

	if (md_check_no_bitmap(mddev))
		return -EINVAL;
	conf = linear_conf(mddev, mddev->raid_disks);

	if (!conf)
		return 1;
	mddev->private = conf;
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));

	ret =  md_integrity_register(mddev);
	if (ret) {
		kfree(conf);
		mddev->private = NULL;
	}
	return ret;
}