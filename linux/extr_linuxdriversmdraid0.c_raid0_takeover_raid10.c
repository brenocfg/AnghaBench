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
typedef  void r0conf ;
struct mddev {int layout; int raid_disks; int degraded; int delta_disks; int /*<<< orphan*/  recovery_cp; int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  new_chunk_sectors; scalar_t__ new_layout; scalar_t__ new_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  UNSUPPORTED_MDDEV_FLAGS ; 
 int /*<<< orphan*/  create_strip_zones (struct mddev*,void**) ; 
 int /*<<< orphan*/  mddev_clear_unsupported_flags (struct mddev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void *raid0_takeover_raid10(struct mddev *mddev)
{
	struct r0conf *priv_conf;

	/* Check layout:
	 *  - far_copies must be 1
	 *  - near_copies must be 2
	 *  - disks number must be even
	 *  - all mirrors must be already degraded
	 */
	if (mddev->layout != ((1 << 8) + 2)) {
		pr_warn("md/raid0:%s:: Raid0 cannot takeover layout: 0x%x\n",
			mdname(mddev),
			mddev->layout);
		return ERR_PTR(-EINVAL);
	}
	if (mddev->raid_disks & 1) {
		pr_warn("md/raid0:%s: Raid0 cannot takeover Raid10 with odd disk number.\n",
			mdname(mddev));
		return ERR_PTR(-EINVAL);
	}
	if (mddev->degraded != (mddev->raid_disks>>1)) {
		pr_warn("md/raid0:%s: All mirrors must be already degraded!\n",
			mdname(mddev));
		return ERR_PTR(-EINVAL);
	}

	/* Set new parameters */
	mddev->new_level = 0;
	mddev->new_layout = 0;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->delta_disks = - mddev->raid_disks / 2;
	mddev->raid_disks += mddev->delta_disks;
	mddev->degraded = 0;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;
	mddev_clear_unsupported_flags(mddev, UNSUPPORTED_MDDEV_FLAGS);

	create_strip_zones(mddev, &priv_conf);
	return priv_conf;
}