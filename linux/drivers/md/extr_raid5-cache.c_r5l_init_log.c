#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
struct r5l_payload_data_parity {int dummy; } ;
struct r5l_meta_block {int dummy; } ;
struct r5l_log {int need_cache_flush; int /*<<< orphan*/  io_kc; int /*<<< orphan*/  io_pool; int /*<<< orphan*/  bs; int /*<<< orphan*/  meta_pool; int /*<<< orphan*/  stripe_in_journal_count; int /*<<< orphan*/  stripe_in_journal_lock; int /*<<< orphan*/  stripe_in_journal_list; int /*<<< orphan*/  r5c_journal_mode; int /*<<< orphan*/  disable_writeback_work; int /*<<< orphan*/  deferred_io_work; int /*<<< orphan*/  no_space_stripes_lock; int /*<<< orphan*/  no_space_stripes; int /*<<< orphan*/  no_mem_stripes; int /*<<< orphan*/  iounit_wait; TYPE_2__* reclaim_thread; struct md_rdev* rdev; int /*<<< orphan*/  big_stripe_tree; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  flush_bio; int /*<<< orphan*/  finished_ios; int /*<<< orphan*/  flushing_ios; int /*<<< orphan*/  io_end_ios; int /*<<< orphan*/  running_ios; int /*<<< orphan*/  io_list_lock; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  uuid_checksum; } ;
struct r5conf {int raid_disks; TYPE_1__* mddev; int /*<<< orphan*/  log; } ;
struct md_rdev {TYPE_3__* mddev; int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  uuid; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  BIOSET_NEED_BVECS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KMEM_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD_HAS_JOURNAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_WC ; 
 int /*<<< orphan*/  R5C_JOURNAL_MODE_WRITE_THROUGH ; 
 int /*<<< orphan*/  R5C_RECLAIM_WAKEUP_INTERVAL ; 
 int /*<<< orphan*/  R5L_POOL_SIZE ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct request_queue* bdev_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioset_exit (int /*<<< orphan*/ *) ; 
 int bioset_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32c_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct r5l_log*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 struct r5l_log* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* md_register_thread (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  mdname (TYPE_1__*) ; 
 int /*<<< orphan*/  mempool_exit (int /*<<< orphan*/ *) ; 
 int mempool_init_page_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mempool_init_slab_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r5c_disable_writeback_async ; 
 int /*<<< orphan*/  r5l_io_unit ; 
 int /*<<< orphan*/  r5l_reclaim_thread ; 
 int /*<<< orphan*/  r5l_submit_io_async ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct r5l_log*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int r5l_init_log(struct r5conf *conf, struct md_rdev *rdev)
{
	struct request_queue *q = bdev_get_queue(rdev->bdev);
	struct r5l_log *log;
	char b[BDEVNAME_SIZE];
	int ret;

	pr_debug("md/raid:%s: using device %s as journal\n",
		 mdname(conf->mddev), bdevname(rdev->bdev, b));

	if (PAGE_SIZE != 4096)
		return -EINVAL;

	/*
	 * The PAGE_SIZE must be big enough to hold 1 r5l_meta_block and
	 * raid_disks r5l_payload_data_parity.
	 *
	 * Write journal and cache does not work for very big array
	 * (raid_disks > 203)
	 */
	if (sizeof(struct r5l_meta_block) +
	    ((sizeof(struct r5l_payload_data_parity) + sizeof(__le32)) *
	     conf->raid_disks) > PAGE_SIZE) {
		pr_err("md/raid:%s: write journal/cache doesn't work for array with %d disks\n",
		       mdname(conf->mddev), conf->raid_disks);
		return -EINVAL;
	}

	log = kzalloc(sizeof(*log), GFP_KERNEL);
	if (!log)
		return -ENOMEM;
	log->rdev = rdev;

	log->need_cache_flush = test_bit(QUEUE_FLAG_WC, &q->queue_flags) != 0;

	log->uuid_checksum = crc32c_le(~0, rdev->mddev->uuid,
				       sizeof(rdev->mddev->uuid));

	mutex_init(&log->io_mutex);

	spin_lock_init(&log->io_list_lock);
	INIT_LIST_HEAD(&log->running_ios);
	INIT_LIST_HEAD(&log->io_end_ios);
	INIT_LIST_HEAD(&log->flushing_ios);
	INIT_LIST_HEAD(&log->finished_ios);
	bio_init(&log->flush_bio, NULL, 0);

	log->io_kc = KMEM_CACHE(r5l_io_unit, 0);
	if (!log->io_kc)
		goto io_kc;

	ret = mempool_init_slab_pool(&log->io_pool, R5L_POOL_SIZE, log->io_kc);
	if (ret)
		goto io_pool;

	ret = bioset_init(&log->bs, R5L_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	if (ret)
		goto io_bs;

	ret = mempool_init_page_pool(&log->meta_pool, R5L_POOL_SIZE, 0);
	if (ret)
		goto out_mempool;

	spin_lock_init(&log->tree_lock);
	INIT_RADIX_TREE(&log->big_stripe_tree, GFP_NOWAIT | __GFP_NOWARN);

	log->reclaim_thread = md_register_thread(r5l_reclaim_thread,
						 log->rdev->mddev, "reclaim");
	if (!log->reclaim_thread)
		goto reclaim_thread;
	log->reclaim_thread->timeout = R5C_RECLAIM_WAKEUP_INTERVAL;

	init_waitqueue_head(&log->iounit_wait);

	INIT_LIST_HEAD(&log->no_mem_stripes);

	INIT_LIST_HEAD(&log->no_space_stripes);
	spin_lock_init(&log->no_space_stripes_lock);

	INIT_WORK(&log->deferred_io_work, r5l_submit_io_async);
	INIT_WORK(&log->disable_writeback_work, r5c_disable_writeback_async);

	log->r5c_journal_mode = R5C_JOURNAL_MODE_WRITE_THROUGH;
	INIT_LIST_HEAD(&log->stripe_in_journal_list);
	spin_lock_init(&log->stripe_in_journal_lock);
	atomic_set(&log->stripe_in_journal_count, 0);

	rcu_assign_pointer(conf->log, log);

	set_bit(MD_HAS_JOURNAL, &conf->mddev->flags);
	return 0;

reclaim_thread:
	mempool_exit(&log->meta_pool);
out_mempool:
	bioset_exit(&log->bs);
io_bs:
	mempool_exit(&log->io_pool);
io_pool:
	kmem_cache_destroy(log->io_kc);
io_kc:
	kfree(log);
	return -EINVAL;
}