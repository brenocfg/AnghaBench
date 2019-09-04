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
struct dmz_metadata {struct dm_zone* sb_zone; int /*<<< orphan*/  nr_rnd_zones; int /*<<< orphan*/  nr_useable_zones; struct dmz_dev* dev; } ;
struct dmz_dev {scalar_t__ zone_nr_sectors; scalar_t__ capacity; } ;
struct dm_zone {scalar_t__ wp_block; int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk; int /*<<< orphan*/  refcount; int /*<<< orphan*/  link; } ;
struct blk_zone {scalar_t__ len; scalar_t__ start; scalar_t__ type; scalar_t__ cond; scalar_t__ wp; } ;

/* Variables and functions */
 scalar_t__ BLK_ZONE_COND_OFFLINE ; 
 scalar_t__ BLK_ZONE_COND_READONLY ; 
 scalar_t__ BLK_ZONE_TYPE_CONVENTIONAL ; 
 scalar_t__ BLK_ZONE_TYPE_SEQWRITE_PREF ; 
 scalar_t__ BLK_ZONE_TYPE_SEQWRITE_REQ ; 
 int /*<<< orphan*/  DMZ_MAP_UNMAPPED ; 
 int /*<<< orphan*/  DMZ_OFFLINE ; 
 int /*<<< orphan*/  DMZ_READ_ONLY ; 
 int /*<<< orphan*/  DMZ_RND ; 
 int /*<<< orphan*/  DMZ_SEQ ; 
 int ENXIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_is_offline (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_is_readonly (struct dm_zone*) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 
 scalar_t__ dmz_sect2blk (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmz_init_zone(struct dmz_metadata *zmd, struct dm_zone *zone,
			 struct blk_zone *blkz)
{
	struct dmz_dev *dev = zmd->dev;

	/* Ignore the eventual last runt (smaller) zone */
	if (blkz->len != dev->zone_nr_sectors) {
		if (blkz->start + blkz->len == dev->capacity)
			return 0;
		return -ENXIO;
	}

	INIT_LIST_HEAD(&zone->link);
	atomic_set(&zone->refcount, 0);
	zone->chunk = DMZ_MAP_UNMAPPED;

	if (blkz->type == BLK_ZONE_TYPE_CONVENTIONAL) {
		set_bit(DMZ_RND, &zone->flags);
		zmd->nr_rnd_zones++;
	} else if (blkz->type == BLK_ZONE_TYPE_SEQWRITE_REQ ||
		   blkz->type == BLK_ZONE_TYPE_SEQWRITE_PREF) {
		set_bit(DMZ_SEQ, &zone->flags);
	} else
		return -ENXIO;

	if (blkz->cond == BLK_ZONE_COND_OFFLINE)
		set_bit(DMZ_OFFLINE, &zone->flags);
	else if (blkz->cond == BLK_ZONE_COND_READONLY)
		set_bit(DMZ_READ_ONLY, &zone->flags);

	if (dmz_is_rnd(zone))
		zone->wp_block = 0;
	else
		zone->wp_block = dmz_sect2blk(blkz->wp - blkz->start);

	if (!dmz_is_offline(zone) && !dmz_is_readonly(zone)) {
		zmd->nr_useable_zones++;
		if (dmz_is_rnd(zone)) {
			zmd->nr_rnd_zones++;
			if (!zmd->sb_zone) {
				/* Super block zone */
				zmd->sb_zone = zone;
			}
		}
	}

	return 0;
}