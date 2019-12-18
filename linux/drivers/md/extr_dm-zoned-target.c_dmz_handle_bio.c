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
struct dmz_target {TYPE_1__* dev; int /*<<< orphan*/  reclaim; struct dmz_metadata* metadata; } ;
struct dmz_metadata {int dummy; } ;
struct dmz_bioctx {struct dm_zone* zone; } ;
struct dm_zone {int dummy; } ;
struct dm_chunk_work {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int DMZ_BDEV_DYING ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct dm_zone*) ; 
 int PTR_ERR (struct dm_zone*) ; 
#define  REQ_OP_DISCARD 131 
#define  REQ_OP_READ 130 
#define  REQ_OP_WRITE 129 
#define  REQ_OP_WRITE_ZEROES 128 
 int bio_op (struct bio*) ; 
 struct dmz_bioctx* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  dmz_activate_zone (struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_bio_chunk (TYPE_1__*,struct bio*) ; 
 int /*<<< orphan*/  dmz_bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_dev_err (TYPE_1__*,char*,int) ; 
 struct dm_zone* dmz_get_chunk_mapping (struct dmz_metadata*,int /*<<< orphan*/ ,int) ; 
 int dmz_handle_discard (struct dmz_target*,struct dm_zone*,struct bio*) ; 
 int dmz_handle_read (struct dmz_target*,struct dm_zone*,struct bio*) ; 
 int dmz_handle_write (struct dmz_target*,struct dm_zone*,struct bio*) ; 
 int /*<<< orphan*/  dmz_lock_metadata (struct dmz_metadata*) ; 
 int /*<<< orphan*/  dmz_put_chunk_mapping (struct dmz_metadata*,struct dm_zone*) ; 
 int /*<<< orphan*/  dmz_schedule_reclaim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_unlock_metadata (struct dmz_metadata*) ; 
 int /*<<< orphan*/  errno_to_blk_status (int) ; 

__attribute__((used)) static void dmz_handle_bio(struct dmz_target *dmz, struct dm_chunk_work *cw,
			   struct bio *bio)
{
	struct dmz_bioctx *bioctx = dm_per_bio_data(bio, sizeof(struct dmz_bioctx));
	struct dmz_metadata *zmd = dmz->metadata;
	struct dm_zone *zone;
	int ret;

	/*
	 * Write may trigger a zone allocation. So make sure the
	 * allocation can succeed.
	 */
	if (bio_op(bio) == REQ_OP_WRITE)
		dmz_schedule_reclaim(dmz->reclaim);

	dmz_lock_metadata(zmd);

	if (dmz->dev->flags & DMZ_BDEV_DYING) {
		ret = -EIO;
		goto out;
	}

	/*
	 * Get the data zone mapping the chunk. There may be no
	 * mapping for read and discard. If a mapping is obtained,
	 + the zone returned will be set to active state.
	 */
	zone = dmz_get_chunk_mapping(zmd, dmz_bio_chunk(dmz->dev, bio),
				     bio_op(bio));
	if (IS_ERR(zone)) {
		ret = PTR_ERR(zone);
		goto out;
	}

	/* Process the BIO */
	if (zone) {
		dmz_activate_zone(zone);
		bioctx->zone = zone;
	}

	switch (bio_op(bio)) {
	case REQ_OP_READ:
		ret = dmz_handle_read(dmz, zone, bio);
		break;
	case REQ_OP_WRITE:
		ret = dmz_handle_write(dmz, zone, bio);
		break;
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
		ret = dmz_handle_discard(dmz, zone, bio);
		break;
	default:
		dmz_dev_err(dmz->dev, "Unsupported BIO operation 0x%x",
			    bio_op(bio));
		ret = -EIO;
	}

	/*
	 * Release the chunk mapping. This will check that the mapping
	 * is still valid, that is, that the zone used still has valid blocks.
	 */
	if (zone)
		dmz_put_chunk_mapping(zmd, zone);
out:
	dmz_bio_endio(bio, errno_to_blk_status(ret));

	dmz_unlock_metadata(zmd);
}