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
struct dmz_metadata {struct dmz_dev* dev; } ;
struct dmz_dev {int /*<<< orphan*/  zone_nr_sectors; int /*<<< orphan*/  bdev; } ;
struct dm_zone {scalar_t__ wp_block; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_SEQ_WRITE_ERR ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int blkdev_reset_zones (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_dev_err (struct dmz_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_is_empty (struct dm_zone*) ; 
 scalar_t__ dmz_is_offline (struct dm_zone*) ; 
 scalar_t__ dmz_is_readonly (struct dm_zone*) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 
 scalar_t__ dmz_seq_write_err (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_start_sect (struct dmz_metadata*,struct dm_zone*) ; 

__attribute__((used)) static int dmz_reset_zone(struct dmz_metadata *zmd, struct dm_zone *zone)
{
	int ret;

	/*
	 * Ignore offline zones, read only zones,
	 * and conventional zones.
	 */
	if (dmz_is_offline(zone) ||
	    dmz_is_readonly(zone) ||
	    dmz_is_rnd(zone))
		return 0;

	if (!dmz_is_empty(zone) || dmz_seq_write_err(zone)) {
		struct dmz_dev *dev = zmd->dev;

		ret = blkdev_reset_zones(dev->bdev,
					 dmz_start_sect(zmd, zone),
					 dev->zone_nr_sectors, GFP_NOIO);
		if (ret) {
			dmz_dev_err(dev, "Reset zone %u failed %d",
				    dmz_id(zmd, zone), ret);
			return ret;
		}
	}

	/* Clear write error bit and rewind write pointer position */
	clear_bit(DMZ_SEQ_WRITE_ERR, &zone->flags);
	zone->wp_block = 0;

	return 0;
}