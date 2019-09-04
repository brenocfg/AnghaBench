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
struct mddev {int level; scalar_t__ layout; scalar_t__ bitmap; } ;

/* Variables and functions */
 scalar_t__ ALGORITHM_PARITY_N ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 void* raid0_takeover_raid1 (struct mddev*) ; 
 void* raid0_takeover_raid10 (struct mddev*) ; 
 void* raid0_takeover_raid45 (struct mddev*) ; 

__attribute__((used)) static void *raid0_takeover(struct mddev *mddev)
{
	/* raid0 can take over:
	 *  raid4 - if all data disks are active.
	 *  raid5 - providing it is Raid4 layout and one disk is faulty
	 *  raid10 - assuming we have all necessary active disks
	 *  raid1 - with (N -1) mirror drives faulty
	 */

	if (mddev->bitmap) {
		pr_warn("md/raid0: %s: cannot takeover array with bitmap\n",
			mdname(mddev));
		return ERR_PTR(-EBUSY);
	}
	if (mddev->level == 4)
		return raid0_takeover_raid45(mddev);

	if (mddev->level == 5) {
		if (mddev->layout == ALGORITHM_PARITY_N)
			return raid0_takeover_raid45(mddev);

		pr_warn("md/raid0:%s: Raid can only takeover Raid5 with layout: %d\n",
			mdname(mddev), ALGORITHM_PARITY_N);
	}

	if (mddev->level == 10)
		return raid0_takeover_raid10(mddev);

	if (mddev->level == 1)
		return raid0_takeover_raid1(mddev);

	pr_warn("Takeover from raid%i to raid0 not supported\n",
		mddev->level);

	return ERR_PTR(-EINVAL);
}