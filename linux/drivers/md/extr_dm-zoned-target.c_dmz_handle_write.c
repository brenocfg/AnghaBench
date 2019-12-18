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
struct dmz_target {int /*<<< orphan*/  metadata; int /*<<< orphan*/  dev; } ;
struct dm_zone {scalar_t__ wp_block; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  dmz_bio_block (struct bio*) ; 
 unsigned int dmz_bio_blocks (struct bio*) ; 
 scalar_t__ dmz_bio_chunk (int /*<<< orphan*/ ,struct bio*) ; 
 scalar_t__ dmz_chunk_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_dev_debug (int /*<<< orphan*/ ,char*,unsigned long long,char*,int /*<<< orphan*/ ,unsigned long long,unsigned int) ; 
 int dmz_handle_buffered_write (struct dmz_target*,struct dm_zone*,struct bio*,scalar_t__,unsigned int) ; 
 int dmz_handle_direct_write (struct dmz_target*,struct dm_zone*,struct bio*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  dmz_id (int /*<<< orphan*/ ,struct dm_zone*) ; 
 scalar_t__ dmz_is_rnd (struct dm_zone*) ; 

__attribute__((used)) static int dmz_handle_write(struct dmz_target *dmz, struct dm_zone *zone,
			    struct bio *bio)
{
	sector_t chunk_block = dmz_chunk_block(dmz->dev, dmz_bio_block(bio));
	unsigned int nr_blocks = dmz_bio_blocks(bio);

	if (!zone)
		return -ENOSPC;

	dmz_dev_debug(dmz->dev, "WRITE chunk %llu -> %s zone %u, block %llu, %u blocks",
		      (unsigned long long)dmz_bio_chunk(dmz->dev, bio),
		      (dmz_is_rnd(zone) ? "RND" : "SEQ"),
		      dmz_id(dmz->metadata, zone),
		      (unsigned long long)chunk_block, nr_blocks);

	if (dmz_is_rnd(zone) || chunk_block == zone->wp_block) {
		/*
		 * zone is a random zone or it is a sequential zone
		 * and the BIO is aligned to the zone write pointer:
		 * direct write the zone.
		 */
		return dmz_handle_direct_write(dmz, zone, bio, chunk_block, nr_blocks);
	}

	/*
	 * This is an unaligned write in a sequential zone:
	 * use buffered write.
	 */
	return dmz_handle_buffered_write(dmz, zone, bio, chunk_block, nr_blocks);
}