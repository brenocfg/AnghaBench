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
struct dmz_mblock {int /*<<< orphan*/  data; } ;
struct dm_zone {int /*<<< orphan*/  weight; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ zone_nr_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 scalar_t__ DMZ_BLOCK_SIZE_BITS ; 
 scalar_t__ IS_ERR (struct dmz_mblock*) ; 
 int PTR_ERR (struct dmz_mblock*) ; 
 int /*<<< orphan*/  dmz_dirty_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 struct dmz_mblock* dmz_get_bitmap (struct dmz_metadata*,struct dm_zone*,scalar_t__) ; 
 int /*<<< orphan*/  dmz_release_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dmz_copy_valid_blocks(struct dmz_metadata *zmd, struct dm_zone *from_zone,
			  struct dm_zone *to_zone)
{
	struct dmz_mblock *from_mblk, *to_mblk;
	sector_t chunk_block = 0;

	/* Get the zones bitmap blocks */
	while (chunk_block < zmd->dev->zone_nr_blocks) {
		from_mblk = dmz_get_bitmap(zmd, from_zone, chunk_block);
		if (IS_ERR(from_mblk))
			return PTR_ERR(from_mblk);
		to_mblk = dmz_get_bitmap(zmd, to_zone, chunk_block);
		if (IS_ERR(to_mblk)) {
			dmz_release_mblock(zmd, from_mblk);
			return PTR_ERR(to_mblk);
		}

		memcpy(to_mblk->data, from_mblk->data, DMZ_BLOCK_SIZE);
		dmz_dirty_mblock(zmd, to_mblk);

		dmz_release_mblock(zmd, to_mblk);
		dmz_release_mblock(zmd, from_mblk);

		chunk_block += DMZ_BLOCK_SIZE_BITS;
	}

	to_zone->weight = from_zone->weight;

	return 0;
}