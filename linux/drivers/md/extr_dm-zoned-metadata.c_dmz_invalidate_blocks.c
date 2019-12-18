#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct dmz_metadata {TYPE_1__* dev; } ;
struct dmz_mblock {scalar_t__ data; } ;
struct dm_zone {unsigned int weight; } ;
typedef  unsigned int sector_t ;
struct TYPE_3__ {unsigned int zone_nr_blocks; } ;

/* Variables and functions */
 unsigned int DMZ_BLOCK_MASK_BITS ; 
 scalar_t__ DMZ_BLOCK_SIZE_BITS ; 
 scalar_t__ IS_ERR (struct dmz_mblock*) ; 
 int PTR_ERR (struct dmz_mblock*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned int dmz_clear_bits (unsigned long*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dmz_dev_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dmz_dev_warn (TYPE_1__*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dmz_dirty_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 struct dmz_mblock* dmz_get_bitmap (struct dmz_metadata*,struct dm_zone*,unsigned int) ; 
 int /*<<< orphan*/  dmz_id (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_release_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 unsigned int min (unsigned int,scalar_t__) ; 

int dmz_invalidate_blocks(struct dmz_metadata *zmd, struct dm_zone *zone,
			  sector_t chunk_block, unsigned int nr_blocks)
{
	unsigned int count, bit, nr_bits;
	struct dmz_mblock *mblk;
	unsigned int n = 0;

	dmz_dev_debug(zmd->dev, "=> INVALIDATE zone %u, block %llu, %u blocks",
		      dmz_id(zmd, zone), (u64)chunk_block, nr_blocks);

	WARN_ON(chunk_block + nr_blocks > zmd->dev->zone_nr_blocks);

	while (nr_blocks) {
		/* Get bitmap block */
		mblk = dmz_get_bitmap(zmd, zone, chunk_block);
		if (IS_ERR(mblk))
			return PTR_ERR(mblk);

		/* Clear bits */
		bit = chunk_block & DMZ_BLOCK_MASK_BITS;
		nr_bits = min(nr_blocks, DMZ_BLOCK_SIZE_BITS - bit);

		count = dmz_clear_bits((unsigned long *)mblk->data,
				       bit, nr_bits);
		if (count) {
			dmz_dirty_mblock(zmd, mblk);
			n += count;
		}
		dmz_release_mblock(zmd, mblk);

		nr_blocks -= nr_bits;
		chunk_block += nr_bits;
	}

	if (zone->weight >= n)
		zone->weight -= n;
	else {
		dmz_dev_warn(zmd->dev, "Zone %u: weight %u should be >= %u",
			     dmz_id(zmd, zone), zone->weight, n);
		zone->weight = 0;
	}

	return 0;
}