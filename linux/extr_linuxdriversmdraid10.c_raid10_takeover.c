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
struct r0conf {int nr_strip_zones; TYPE_1__* strip_zone; } ;
struct mddev {scalar_t__ level; struct r0conf* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  nb_dev; int /*<<< orphan*/  zone_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 void* raid10_takeover_raid0 (struct mddev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *raid10_takeover(struct mddev *mddev)
{
	struct r0conf *raid0_conf;

	/* raid10 can take over:
	 *  raid0 - providing it has only two drives
	 */
	if (mddev->level == 0) {
		/* for raid0 takeover only one zone is supported */
		raid0_conf = mddev->private;
		if (raid0_conf->nr_strip_zones > 1) {
			pr_warn("md/raid10:%s: cannot takeover raid 0 with more than one zone.\n",
				mdname(mddev));
			return ERR_PTR(-EINVAL);
		}
		return raid10_takeover_raid0(mddev,
			raid0_conf->strip_zone->zone_end,
			raid0_conf->strip_zone->nb_dev);
	}
	return ERR_PTR(-EINVAL);
}