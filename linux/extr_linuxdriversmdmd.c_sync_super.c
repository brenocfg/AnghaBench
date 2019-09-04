#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mddev {size_t major_version; int /*<<< orphan*/  (* sync_super ) (struct mddev*,struct md_rdev*) ;} ;
struct md_rdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* sync_super ) (struct mddev*,struct md_rdev*) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct mddev*,struct md_rdev*) ; 
 int /*<<< orphan*/  stub2 (struct mddev*,struct md_rdev*) ; 
 TYPE_1__* super_types ; 

__attribute__((used)) static void sync_super(struct mddev *mddev, struct md_rdev *rdev)
{
	if (mddev->sync_super) {
		mddev->sync_super(mddev, rdev);
		return;
	}

	BUG_ON(mddev->major_version >= ARRAY_SIZE(super_types));

	super_types[mddev->major_version].sync_super(mddev, rdev);
}