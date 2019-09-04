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
struct md_rdev {int /*<<< orphan*/  kobj; TYPE_1__* bdev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AutoDetected ; 
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  bdevname (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_autodetect_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_rdev_clear (struct md_rdev*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_rdev (struct md_rdev*) ; 

__attribute__((used)) static void export_rdev(struct md_rdev *rdev)
{
	char b[BDEVNAME_SIZE];

	pr_debug("md: export_rdev(%s)\n", bdevname(rdev->bdev,b));
	md_rdev_clear(rdev);
#ifndef MODULE
	if (test_bit(AutoDetected, &rdev->flags))
		md_autodetect_dev(rdev->bdev->bd_dev);
#endif
	unlock_rdev(rdev);
	kobject_put(&rdev->kobj);
}