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
struct r5conf {int /*<<< orphan*/  log; int /*<<< orphan*/  cache_size_mutex; int /*<<< orphan*/  cache_state; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  temp_inactive_list; scalar_t__ seq_flush; scalar_t__ seq_write; int /*<<< orphan*/  bitmap_list; } ;
struct mddev {int sb_flags; int /*<<< orphan*/  bitmap; struct r5conf* private; } ;
struct md_thread {struct mddev* mddev; } ;
struct blk_plug {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANY_GROUP ; 
 int MD_SB_CHANGE_PENDING ; 
 int /*<<< orphan*/  R5_ALLOC_MORE ; 
 int /*<<< orphan*/  R5_DID_ALLOC ; 
 int /*<<< orphan*/  __GFP_NOWARN ; 
 int /*<<< orphan*/  activate_bit_delay (struct r5conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_tx_issue_pending_all () ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_deferred_bios (struct r5conf*) ; 
 int /*<<< orphan*/  grow_one_stripe (struct r5conf*,int /*<<< orphan*/ ) ; 
 int handle_active_stripes (struct r5conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_bitmap_unplug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_check_recovery (struct mddev*) ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  r5l_flush_stripe_to_raid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_activate_delayed (struct r5conf*) ; 
 int release_stripe_list (struct r5conf*,int /*<<< orphan*/ ) ; 
 struct bio* remove_bio_from_retry (struct r5conf*,unsigned int*) ; 
 int retry_aligned_read (struct r5conf*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid5d(struct md_thread *thread)
{
	struct mddev *mddev = thread->mddev;
	struct r5conf *conf = mddev->private;
	int handled;
	struct blk_plug plug;

	pr_debug("+++ raid5d active\n");

	md_check_recovery(mddev);

	blk_start_plug(&plug);
	handled = 0;
	spin_lock_irq(&conf->device_lock);
	while (1) {
		struct bio *bio;
		int batch_size, released;
		unsigned int offset;

		released = release_stripe_list(conf, conf->temp_inactive_list);
		if (released)
			clear_bit(R5_DID_ALLOC, &conf->cache_state);

		if (
		    !list_empty(&conf->bitmap_list)) {
			/* Now is a good time to flush some bitmap updates */
			conf->seq_flush++;
			spin_unlock_irq(&conf->device_lock);
			md_bitmap_unplug(mddev->bitmap);
			spin_lock_irq(&conf->device_lock);
			conf->seq_write = conf->seq_flush;
			activate_bit_delay(conf, conf->temp_inactive_list);
		}
		raid5_activate_delayed(conf);

		while ((bio = remove_bio_from_retry(conf, &offset))) {
			int ok;
			spin_unlock_irq(&conf->device_lock);
			ok = retry_aligned_read(conf, bio, offset);
			spin_lock_irq(&conf->device_lock);
			if (!ok)
				break;
			handled++;
		}

		batch_size = handle_active_stripes(conf, ANY_GROUP, NULL,
						   conf->temp_inactive_list);
		if (!batch_size && !released)
			break;
		handled += batch_size;

		if (mddev->sb_flags & ~(1 << MD_SB_CHANGE_PENDING)) {
			spin_unlock_irq(&conf->device_lock);
			md_check_recovery(mddev);
			spin_lock_irq(&conf->device_lock);
		}
	}
	pr_debug("%d stripes handled\n", handled);

	spin_unlock_irq(&conf->device_lock);
	if (test_and_clear_bit(R5_ALLOC_MORE, &conf->cache_state) &&
	    mutex_trylock(&conf->cache_size_mutex)) {
		grow_one_stripe(conf, __GFP_NOWARN);
		/* Set flag even if allocation failed.  This helps
		 * slow down allocation requests when mem is short
		 */
		set_bit(R5_DID_ALLOC, &conf->cache_state);
		mutex_unlock(&conf->cache_size_mutex);
	}

	flush_deferred_bios(conf);

	r5l_flush_stripe_to_raid(conf->log);

	async_tx_issue_pending_all();
	blk_finish_plug(&plug);

	pr_debug("--- raid5d inactive\n");
}