#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raid_type {unsigned int parity_devs; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  level; } ;
struct TYPE_4__ {unsigned int raid_disks; int /*<<< orphan*/  recovery_cp; scalar_t__ delta_disks; int /*<<< orphan*/  layout; int /*<<< orphan*/  new_layout; int /*<<< orphan*/  level; int /*<<< orphan*/  new_level; } ;
struct raid_set {unsigned int raid_disks; int stripe_cache_entries; TYPE_1__* dev; TYPE_2__ md; struct raid_type* raid_type; struct dm_target* ti; scalar_t__ delta_disks; } ;
struct dm_target {char* error; } ;
struct TYPE_3__ {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct raid_set* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  dev ; 
 struct raid_set* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_rdev_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mddev_init (TYPE_2__*) ; 
 int /*<<< orphan*/  struct_size (struct raid_set*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct raid_set *raid_set_alloc(struct dm_target *ti, struct raid_type *raid_type,
				       unsigned int raid_devs)
{
	unsigned int i;
	struct raid_set *rs;

	if (raid_devs <= raid_type->parity_devs) {
		ti->error = "Insufficient number of devices";
		return ERR_PTR(-EINVAL);
	}

	rs = kzalloc(struct_size(rs, dev, raid_devs), GFP_KERNEL);
	if (!rs) {
		ti->error = "Cannot allocate raid context";
		return ERR_PTR(-ENOMEM);
	}

	mddev_init(&rs->md);

	rs->raid_disks = raid_devs;
	rs->delta_disks = 0;

	rs->ti = ti;
	rs->raid_type = raid_type;
	rs->stripe_cache_entries = 256;
	rs->md.raid_disks = raid_devs;
	rs->md.level = raid_type->level;
	rs->md.new_level = rs->md.level;
	rs->md.layout = raid_type->algorithm;
	rs->md.new_layout = rs->md.layout;
	rs->md.delta_disks = 0;
	rs->md.recovery_cp = MaxSector;

	for (i = 0; i < raid_devs; i++)
		md_rdev_init(&rs->dev[i].rdev);

	/*
	 * Remaining items to be initialized by further RAID params:
	 *  rs->md.persistent
	 *  rs->md.external
	 *  rs->md.chunk_sectors
	 *  rs->md.new_chunk_sectors
	 *  rs->md.dev_sectors
	 */

	return rs;
}