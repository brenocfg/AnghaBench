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
struct dm_zone {unsigned int chunk; } ;
struct TYPE_2__ {int /*<<< orphan*/  zone_nr_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_ALLOC_RECLAIM ; 
 int ENOSPC ; 
 struct dm_zone* dmz_alloc_zone (struct dmz_metadata*,int /*<<< orphan*/ ) ; 
 int dmz_copy_valid_blocks (struct dmz_metadata*,struct dm_zone*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_dev_debug (TYPE_1__*,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_free_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_invalidate_blocks (struct dmz_metadata*,struct dm_zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_lock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_lock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_map_zone (struct dmz_metadata*,struct dm_zone*,unsigned int) ; 
 int dmz_reclaim_copy (struct dmz_reclaim*,struct dm_zone*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unlock_flush (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_map (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_unlock_zone_reclaim (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unmap_zone (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_weight (struct dm_zone*) ; 

__attribute__((used)) static int dmz_reclaim_rnd_data(struct dmz_reclaim *zrc, struct dm_zone *dzone)
{
	unsigned int chunk = dzone->chunk;
	struct dm_zone *szone = NULL;
	struct dmz_metadata *zmd = zrc->metadata;
	int ret;

	/* Get a free sequential zone */
	dmz_lock_map(zmd);
	szone = dmz_alloc_zone(zmd, DMZ_ALLOC_RECLAIM);
	dmz_unlock_map(zmd);
	if (!szone)
		return -ENOSPC;

	dmz_dev_debug(zrc->dev,
		      "Chunk %u, move rnd zone %u (weight %u) to seq zone %u",
		      chunk, dmz_id(zmd, dzone), dmz_weight(dzone),
		      dmz_id(zmd, szone));

	/* Flush the random data zone into the sequential zone */
	ret = dmz_reclaim_copy(zrc, dzone, szone);

	dmz_lock_flush(zmd);

	if (ret == 0) {
		/* Validate copied blocks */
		ret = dmz_copy_valid_blocks(zmd, dzone, szone);
	}
	if (ret) {
		/* Free the sequential zone */
		dmz_lock_map(zmd);
		dmz_free_zone(zmd, szone);
		dmz_unlock_map(zmd);
	} else {
		/* Free the data zone and remap the chunk */
		dmz_invalidate_blocks(zmd, dzone, 0, zrc->dev->zone_nr_blocks);
		dmz_lock_map(zmd);
		dmz_unmap_zone(zmd, dzone);
		dmz_unlock_zone_reclaim(dzone);
		dmz_free_zone(zmd, dzone);
		dmz_map_zone(zmd, szone, chunk);
		dmz_unlock_map(zmd);
	}

	dmz_unlock_flush(zmd);

	return ret;
}