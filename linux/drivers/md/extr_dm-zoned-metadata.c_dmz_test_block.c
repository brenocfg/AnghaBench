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
struct dmz_mblock {scalar_t__ data; } ;
struct dm_zone {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int zone_nr_blocks; } ;

/* Variables and functions */
 int DMZ_BLOCK_MASK_BITS ; 
 scalar_t__ IS_ERR (struct dmz_mblock*) ; 
 int PTR_ERR (struct dmz_mblock*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct dmz_mblock* dmz_get_bitmap (struct dmz_metadata*,struct dm_zone*,int) ; 
 int /*<<< orphan*/  dmz_release_mblock (struct dmz_metadata*,struct dmz_mblock*) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

__attribute__((used)) static int dmz_test_block(struct dmz_metadata *zmd, struct dm_zone *zone,
			  sector_t chunk_block)
{
	struct dmz_mblock *mblk;
	int ret;

	WARN_ON(chunk_block >= zmd->dev->zone_nr_blocks);

	/* Get bitmap block */
	mblk = dmz_get_bitmap(zmd, zone, chunk_block);
	if (IS_ERR(mblk))
		return PTR_ERR(mblk);

	/* Get offset */
	ret = test_bit(chunk_block & DMZ_BLOCK_MASK_BITS,
		       (unsigned long *) mblk->data) != 0;

	dmz_release_mblock(zmd, mblk);

	return ret;
}