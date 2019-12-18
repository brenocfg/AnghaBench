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
struct mddev {int level; scalar_t__ layout; int new_level; scalar_t__ new_layout; } ;

/* Variables and functions */
 scalar_t__ ALGORITHM_PARITY_N ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* raid45_takeover_raid0 (struct mddev*,int) ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid4_takeover(struct mddev *mddev)
{
	/* raid4 can take over:
	 *  raid0 - if there is only one strip zone
	 *  raid5 - if layout is right
	 */
	if (mddev->level == 0)
		return raid45_takeover_raid0(mddev, 4);
	if (mddev->level == 5 &&
	    mddev->layout == ALGORITHM_PARITY_N) {
		mddev->new_layout = 0;
		mddev->new_level = 4;
		return setup_conf(mddev);
	}
	return ERR_PTR(-EINVAL);
}