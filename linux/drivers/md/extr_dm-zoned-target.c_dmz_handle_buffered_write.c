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
struct dmz_target {struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;
struct dm_zone {scalar_t__ wp_block; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EROFS ; 
 scalar_t__ IS_ERR (struct dm_zone*) ; 
 int PTR_ERR (struct dm_zone*) ; 
 struct dm_zone* dmz_get_chunk_buffer (struct dmz_metadata*,struct dm_zone*) ; 
 int dmz_invalidate_blocks (struct dmz_metadata*,struct dm_zone*,scalar_t__,unsigned int) ; 
 scalar_t__ dmz_is_readonly (struct dm_zone*) ; 
 int dmz_submit_bio (struct dmz_target*,struct dm_zone*,struct bio*,scalar_t__,unsigned int) ; 
 int dmz_validate_blocks (struct dmz_metadata*,struct dm_zone*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int dmz_handle_buffered_write(struct dmz_target *dmz,
				     struct dm_zone *zone, struct bio *bio,
				     sector_t chunk_block,
				     unsigned int nr_blocks)
{
	struct dmz_metadata *zmd = dmz->metadata;
	struct dm_zone *bzone;
	int ret;

	/* Get the buffer zone. One will be allocated if needed */
	bzone = dmz_get_chunk_buffer(zmd, zone);
	if (IS_ERR(bzone))
		return PTR_ERR(bzone);

	if (dmz_is_readonly(bzone))
		return -EROFS;

	/* Submit write */
	ret = dmz_submit_bio(dmz, bzone, bio, chunk_block, nr_blocks);
	if (ret)
		return ret;

	/*
	 * Validate the blocks in the buffer zone
	 * and invalidate in the data zone.
	 */
	ret = dmz_validate_blocks(zmd, bzone, chunk_block, nr_blocks);
	if (ret == 0 && chunk_block < zone->wp_block)
		ret = dmz_invalidate_blocks(zmd, zone, chunk_block, nr_blocks);

	return ret;
}