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
struct TYPE_2__ {scalar_t__ sd; } ;
struct mddev {TYPE_1__ kobj; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  kobj; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Journal ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sysfs_create_link (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int sysfs_link_rdev(struct mddev *mddev, struct md_rdev *rdev)
{
	char nm[20];
	if (!test_bit(Replacement, &rdev->flags) &&
	    !test_bit(Journal, &rdev->flags) &&
	    mddev->kobj.sd) {
		sprintf(nm, "rd%d", rdev->raid_disk);
		return sysfs_create_link(&mddev->kobj, &rdev->kobj, nm);
	} else
		return 0;
}