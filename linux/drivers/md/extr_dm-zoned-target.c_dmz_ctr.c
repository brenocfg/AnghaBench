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
struct dmz_target {int /*<<< orphan*/  metadata; int /*<<< orphan*/  bio_set; int /*<<< orphan*/  chunk_lock; int /*<<< orphan*/  chunk_wq; int /*<<< orphan*/  flush_wq; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  flush_work; int /*<<< orphan*/  flush_list; int /*<<< orphan*/  flush_lock; int /*<<< orphan*/  chunk_rxtree; struct dmz_dev* dev; int /*<<< orphan*/ * ddev; } ;
struct dmz_dev {int zone_nr_sectors; int zone_nr_sectors_shift; int /*<<< orphan*/  name; } ;
struct dmz_bioctx {int dummy; } ;
struct dm_target {char* error; int max_io_len; int num_flush_bios; int num_discard_bios; int num_write_zeroes_bios; int per_io_data_size; int flush_supported; int discards_supported; int len; struct dmz_target* private; } ;
typedef  int sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_FLUSH_PERIOD ; 
 int /*<<< orphan*/  DMZ_MIN_BIOS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int bioset_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int dmz_ctr_metadata (struct dmz_dev*,int /*<<< orphan*/ *) ; 
 int dmz_ctr_reclaim (struct dmz_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_dev_info (struct dmz_dev*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dmz_dtr_metadata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_flush_work ; 
 int dmz_get_zoned_device (struct dm_target*,char*) ; 
 scalar_t__ dmz_nr_chunks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmz_put_zoned_device (struct dm_target*) ; 
 scalar_t__ dmz_sect2blk (int) ; 
 int /*<<< orphan*/  kfree (struct dmz_target*) ; 
 struct dmz_target* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dmz_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct dmz_target *dmz;
	struct dmz_dev *dev;
	int ret;

	/* Check arguments */
	if (argc != 1) {
		ti->error = "Invalid argument count";
		return -EINVAL;
	}

	/* Allocate and initialize the target descriptor */
	dmz = kzalloc(sizeof(struct dmz_target), GFP_KERNEL);
	if (!dmz) {
		ti->error = "Unable to allocate the zoned target descriptor";
		return -ENOMEM;
	}
	ti->private = dmz;

	/* Get the target zoned block device */
	ret = dmz_get_zoned_device(ti, argv[0]);
	if (ret) {
		dmz->ddev = NULL;
		goto err;
	}

	/* Initialize metadata */
	dev = dmz->dev;
	ret = dmz_ctr_metadata(dev, &dmz->metadata);
	if (ret) {
		ti->error = "Metadata initialization failed";
		goto err_dev;
	}

	/* Set target (no write same support) */
	ti->max_io_len = dev->zone_nr_sectors << 9;
	ti->num_flush_bios = 1;
	ti->num_discard_bios = 1;
	ti->num_write_zeroes_bios = 1;
	ti->per_io_data_size = sizeof(struct dmz_bioctx);
	ti->flush_supported = true;
	ti->discards_supported = true;

	/* The exposed capacity is the number of chunks that can be mapped */
	ti->len = (sector_t)dmz_nr_chunks(dmz->metadata) << dev->zone_nr_sectors_shift;

	/* Zone BIO */
	ret = bioset_init(&dmz->bio_set, DMZ_MIN_BIOS, 0, 0);
	if (ret) {
		ti->error = "Create BIO set failed";
		goto err_meta;
	}

	/* Chunk BIO work */
	mutex_init(&dmz->chunk_lock);
	INIT_RADIX_TREE(&dmz->chunk_rxtree, GFP_NOIO);
	dmz->chunk_wq = alloc_workqueue("dmz_cwq_%s", WQ_MEM_RECLAIM | WQ_UNBOUND,
					0, dev->name);
	if (!dmz->chunk_wq) {
		ti->error = "Create chunk workqueue failed";
		ret = -ENOMEM;
		goto err_bio;
	}

	/* Flush work */
	spin_lock_init(&dmz->flush_lock);
	bio_list_init(&dmz->flush_list);
	INIT_DELAYED_WORK(&dmz->flush_work, dmz_flush_work);
	dmz->flush_wq = alloc_ordered_workqueue("dmz_fwq_%s", WQ_MEM_RECLAIM,
						dev->name);
	if (!dmz->flush_wq) {
		ti->error = "Create flush workqueue failed";
		ret = -ENOMEM;
		goto err_cwq;
	}
	mod_delayed_work(dmz->flush_wq, &dmz->flush_work, DMZ_FLUSH_PERIOD);

	/* Initialize reclaim */
	ret = dmz_ctr_reclaim(dev, dmz->metadata, &dmz->reclaim);
	if (ret) {
		ti->error = "Zone reclaim initialization failed";
		goto err_fwq;
	}

	dmz_dev_info(dev, "Target device: %llu 512-byte logical sectors (%llu blocks)",
		     (unsigned long long)ti->len,
		     (unsigned long long)dmz_sect2blk(ti->len));

	return 0;
err_fwq:
	destroy_workqueue(dmz->flush_wq);
err_cwq:
	destroy_workqueue(dmz->chunk_wq);
err_bio:
	mutex_destroy(&dmz->chunk_lock);
	bioset_exit(&dmz->bio_set);
err_meta:
	dmz_dtr_metadata(dmz->metadata);
err_dev:
	dmz_put_zoned_device(ti);
err:
	kfree(dmz);

	return ret;
}