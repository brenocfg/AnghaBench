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
struct dmz_metadata {TYPE_1__* dev; } ;
struct dm_zone {int /*<<< orphan*/  wp_block; int /*<<< orphan*/  flags; } ;
struct blk_zone {scalar_t__ cond; scalar_t__ start; scalar_t__ wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 scalar_t__ BLK_ZONE_COND_OFFLINE ; 
 scalar_t__ BLK_ZONE_COND_READONLY ; 
 int /*<<< orphan*/  DMZ_OFFLINE ; 
 int /*<<< orphan*/  DMZ_READ_ONLY ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int blkdev_report_zones (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct blk_zone*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 scalar_t__ dmz_is_seq (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_sect2blk (scalar_t__) ; 
 int /*<<< orphan*/  dmz_start_sect (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmz_update_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	unsigned int nr_blkz = 1;
	struct blk_zone blkz;
	int ret;

	/* Get zone information from disk */
	ret = blkdev_report_zones(zmd->dev->bdev, dmz_start_sect(zmd, zone),
				  &blkz, &nr_blkz, GFP_NOIO);
	if (ret) {
		dmz_dev_err(zmd->dev, "Get zone %u report failed",
			    dmz_id(zmd, zone));
		return ret;
	}

	clear_bit(DMZ_OFFLINE, &zone->flags);
	clear_bit(DMZ_READ_ONLY, &zone->flags);
	if (blkz.cond == BLK_ZONE_COND_OFFLINE)
		set_bit(DMZ_OFFLINE, &zone->flags);
	else if (blkz.cond == BLK_ZONE_COND_READONLY)
		set_bit(DMZ_READ_ONLY, &zone->flags);

	if (dmz_is_seq(zone))
		zone->wp_block = dmz_sect2blk(blkz.wp - blkz.start);
	else
		zone->wp_block = 0;

	return 0;
}