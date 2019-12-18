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
struct per_bio_data {int dummy; } ;
struct log_writes_c {int sectorsize; int next_sector; int logging_enabled; int device_supports_discard; int /*<<< orphan*/  end_sector; TYPE_1__* logdev; TYPE_1__* dev; int /*<<< orphan*/  log_kthread; int /*<<< orphan*/  sectorshift; int /*<<< orphan*/  pending_blocks; int /*<<< orphan*/  io_blocks; int /*<<< orphan*/  super_done; int /*<<< orphan*/  wait; int /*<<< orphan*/  logging_blocks; int /*<<< orphan*/  unflushed_blocks; int /*<<< orphan*/  blocks_lock; } ;
struct dm_target {char* error; int num_flush_bios; int flush_supported; int num_discard_bios; int discards_supported; int per_io_data_size; struct log_writes_c* private; int /*<<< orphan*/  table; } ;
struct dm_arg_set {unsigned int argc; char** argv; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int dm_get_device (struct dm_target*,char const*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,TYPE_1__*) ; 
 char* dm_shift_arg (struct dm_arg_set*) ; 
 int /*<<< orphan*/  dm_table_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct log_writes_c*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct log_writes_c*,char*) ; 
 struct log_writes_c* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_writes_kthread ; 
 int /*<<< orphan*/  logdev_last_sector (struct log_writes_c*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int log_writes_ctr(struct dm_target *ti, unsigned int argc, char **argv)
{
	struct log_writes_c *lc;
	struct dm_arg_set as;
	const char *devname, *logdevname;
	int ret;

	as.argc = argc;
	as.argv = argv;

	if (argc < 2) {
		ti->error = "Invalid argument count";
		return -EINVAL;
	}

	lc = kzalloc(sizeof(struct log_writes_c), GFP_KERNEL);
	if (!lc) {
		ti->error = "Cannot allocate context";
		return -ENOMEM;
	}
	spin_lock_init(&lc->blocks_lock);
	INIT_LIST_HEAD(&lc->unflushed_blocks);
	INIT_LIST_HEAD(&lc->logging_blocks);
	init_waitqueue_head(&lc->wait);
	init_completion(&lc->super_done);
	atomic_set(&lc->io_blocks, 0);
	atomic_set(&lc->pending_blocks, 0);

	devname = dm_shift_arg(&as);
	ret = dm_get_device(ti, devname, dm_table_get_mode(ti->table), &lc->dev);
	if (ret) {
		ti->error = "Device lookup failed";
		goto bad;
	}

	logdevname = dm_shift_arg(&as);
	ret = dm_get_device(ti, logdevname, dm_table_get_mode(ti->table),
			    &lc->logdev);
	if (ret) {
		ti->error = "Log device lookup failed";
		dm_put_device(ti, lc->dev);
		goto bad;
	}

	lc->sectorsize = bdev_logical_block_size(lc->dev->bdev);
	lc->sectorshift = ilog2(lc->sectorsize);
	lc->log_kthread = kthread_run(log_writes_kthread, lc, "log-write");
	if (IS_ERR(lc->log_kthread)) {
		ret = PTR_ERR(lc->log_kthread);
		ti->error = "Couldn't alloc kthread";
		dm_put_device(ti, lc->dev);
		dm_put_device(ti, lc->logdev);
		goto bad;
	}

	/*
	 * next_sector is in 512b sectors to correspond to what bi_sector expects.
	 * The super starts at sector 0, and the next_sector is the next logical
	 * one based on the sectorsize of the device.
	 */
	lc->next_sector = lc->sectorsize >> SECTOR_SHIFT;
	lc->logging_enabled = true;
	lc->end_sector = logdev_last_sector(lc);
	lc->device_supports_discard = true;

	ti->num_flush_bios = 1;
	ti->flush_supported = true;
	ti->num_discard_bios = 1;
	ti->discards_supported = true;
	ti->per_io_data_size = sizeof(struct per_bio_data);
	ti->private = lc;
	return 0;

bad:
	kfree(lc);
	return ret;
}