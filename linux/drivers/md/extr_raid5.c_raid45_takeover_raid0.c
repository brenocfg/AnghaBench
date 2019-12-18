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
struct mddev {int new_level; int raid_disks; int delta_disks; int /*<<< orphan*/  recovery_cp; int /*<<< orphan*/  chunk_sectors; int /*<<< orphan*/  new_chunk_sectors; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  dev_sectors; struct r0conf* private; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  nb_dev; int /*<<< orphan*/  zone_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGORITHM_PARITY_N ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid45_takeover_raid0(struct mddev *mddev, int level)
{
	struct r0conf *raid0_conf = mddev->private;
	sector_t sectors;

	/* for raid0 takeover only one zone is supported */
	if (raid0_conf->nr_strip_zones > 1) {
		pr_warn("md/raid:%s: cannot takeover raid0 with more than one zone.\n",
			mdname(mddev));
		return ERR_PTR(-EINVAL);
	}

	sectors = raid0_conf->strip_zone[0].zone_end;
	sector_div(sectors, raid0_conf->strip_zone[0].nb_dev);
	mddev->dev_sectors = sectors;
	mddev->new_level = level;
	mddev->new_layout = ALGORITHM_PARITY_N;
	mddev->new_chunk_sectors = mddev->chunk_sectors;
	mddev->raid_disks += 1;
	mddev->delta_disks = 1;
	/* make sure it will be not marked as dirty */
	mddev->recovery_cp = MaxSector;

	return setup_conf(mddev);
}