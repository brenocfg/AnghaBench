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
struct dmz_reclaim {int /*<<< orphan*/  dev; struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;
struct dm_zone {scalar_t__ wp_block; struct dm_zone* bzone; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dm_zone*) ; 
 int PTR_ERR (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_dev_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int dmz_first_valid_block (struct dmz_metadata*,struct dm_zone*,scalar_t__*) ; 
 int dmz_flush_metadata (struct dmz_metadata*) ; 
 struct dm_zone* dmz_get_zone_for_reclaim (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 
 int dmz_reclaim_buf (struct dmz_reclaim*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_reclaim_empty (struct dmz_reclaim*,struct dm_zone*) ; 
 int dmz_reclaim_rnd_data (struct dmz_reclaim*,struct dm_zone*) ; 
 int dmz_reclaim_seq_data (struct dmz_reclaim*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_unlock_zone_reclaim (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_weight (struct dm_zone*) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 

__attribute__((used)) static int dmz_do_reclaim(struct dmz_reclaim *zrc)
{
	struct dmz_metadata *zmd = zrc->metadata;
	struct dm_zone *dzone;
	struct dm_zone *rzone;
	unsigned long start;
	int ret;

	/* Get a data zone */
	dzone = dmz_get_zone_for_reclaim(zmd);
	if (IS_ERR(dzone))
		return PTR_ERR(dzone);

	start = jiffies;

	if (dmz_is_rnd(dzone)) {
		if (!dmz_weight(dzone)) {
			/* Empty zone */
			dmz_reclaim_empty(zrc, dzone);
			ret = 0;
		} else {
			/*
			 * Reclaim the random data zone by moving its
			 * valid data blocks to a free sequential zone.
			 */
			ret = dmz_reclaim_rnd_data(zrc, dzone);
		}
		rzone = dzone;

	} else {
		struct dm_zone *bzone = dzone->bzone;
		sector_t chunk_block = 0;

		ret = dmz_first_valid_block(zmd, bzone, &chunk_block);
		if (ret < 0)
			goto out;

		if (ret == 0 || chunk_block >= dzone->wp_block) {
			/*
			 * The buffer zone is empty or its valid blocks are
			 * after the data zone write pointer.
			 */
			ret = dmz_reclaim_buf(zrc, dzone);
			rzone = bzone;
		} else {
			/*
			 * Reclaim the data zone by merging it into the
			 * buffer zone so that the buffer zone itself can
			 * be later reclaimed.
			 */
			ret = dmz_reclaim_seq_data(zrc, dzone);
			rzone = dzone;
		}
	}
out:
	if (ret) {
		dmz_unlock_zone_reclaim(dzone);
		return ret;
	}

	ret = dmz_flush_metadata(zrc->metadata);
	if (ret) {
		dmz_dev_debug(zrc->dev,
			      "Metadata flush for zone %u failed, err %d\n",
			      dmz_id(zmd, rzone), ret);
		return ret;
	}

	dmz_dev_debug(zrc->dev, "Reclaimed zone %u in %u ms",
		      dmz_id(zmd, rzone), jiffies_to_msecs(jiffies - start));
	return 0;
}