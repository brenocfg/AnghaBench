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
struct dmz_reclaim {TYPE_1__* dev; struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;
struct dm_zone {int /*<<< orphan*/  chunk; int /*<<< orphan*/  wp_block; struct dm_zone* bzone; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  zone_nr_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmz_dev_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_free_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_invalidate_blocks (struct dmz_metadata*,struct dm_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_lock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int dmz_merge_valid_blocks (struct dmz_metadata*,struct dm_zone*,struct dm_zone*,int /*<<< orphan*/ ) ; 
 int dmz_reclaim_copy (struct dmz_reclaim*,struct dm_zone*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unlock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_zone_reclaim (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unmap_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_weight (struct dm_zone*) ; 

__attribute__((used)) static int dmz_reclaim_buf(struct dmz_reclaim *zrc, struct dm_zone *dzone)
{
	struct dm_zone *bzone = dzone->bzone;
	sector_t chunk_block = dzone->wp_block;
	struct dmz_metadata *zmd = zrc->metadata;
	int ret;

	dmz_dev_debug(zrc->dev,
		      "Chunk %u, move buf zone %u (weight %u) to data zone %u (weight %u)",
		      dzone->chunk, dmz_id(zmd, bzone), dmz_weight(bzone),
		      dmz_id(zmd, dzone), dmz_weight(dzone));

	/* Flush data zone into the buffer zone */
	ret = dmz_reclaim_copy(zrc, bzone, dzone);
	if (ret < 0)
		return ret;

	dmz_lock_flush(zmd);

	/* Validate copied blocks */
	ret = dmz_merge_valid_blocks(zmd, bzone, dzone, chunk_block);
	if (ret == 0) {
		/* Free the buffer zone */
		dmz_invalidate_blocks(zmd, bzone, 0, zrc->dev->zone_nr_blocks);
		dmz_lock_map(zmd);
		dmz_unmap_zone(zmd, bzone);
		dmz_unlock_zone_reclaim(dzone);
		dmz_free_zone(zmd, bzone);
		dmz_unlock_map(zmd);
	}

	dmz_unlock_flush(zmd);

	return ret;
}