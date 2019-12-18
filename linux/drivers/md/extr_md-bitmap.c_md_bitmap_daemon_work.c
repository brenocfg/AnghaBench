#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ external; int /*<<< orphan*/  mutex; scalar_t__ daemon_sleep; } ;
struct mddev {TYPE_5__ bitmap_info; TYPE_4__* thread; struct bitmap* bitmap; } ;
struct bitmap_counts {unsigned long chunks; int chunkshift; int /*<<< orphan*/  lock; TYPE_2__* bp; } ;
struct TYPE_11__ {unsigned long file_pages; int /*<<< orphan*/ * filemap; int /*<<< orphan*/  sb_page; } ;
struct bitmap {int allclean; TYPE_3__ storage; int /*<<< orphan*/  flags; scalar_t__ need_sync; struct bitmap_counts counts; int /*<<< orphan*/  events_cleared; TYPE_1__* mddev; scalar_t__ daemon_lastrun; } ;
typedef  int sector_t ;
struct TYPE_14__ {int /*<<< orphan*/  events_cleared; } ;
typedef  TYPE_6__ bitmap_super_t ;
typedef  int bitmap_counter_t ;
struct TYPE_12__ {scalar_t__ timeout; } ;
struct TYPE_10__ {scalar_t__ pending; } ;
struct TYPE_9__ {scalar_t__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_PAGE_DIRTY ; 
 int /*<<< orphan*/  BITMAP_PAGE_NEEDWRITE ; 
 int /*<<< orphan*/  BITMAP_PAGE_PENDING ; 
 int /*<<< orphan*/  BITMAP_STALE ; 
 scalar_t__ MAX_SCHEDULE_TIMEOUT ; 
 unsigned long PAGE_COUNTER_MASK ; 
 scalar_t__ PAGE_COUNTER_RATIO ; 
 unsigned long PAGE_COUNTER_SHIFT ; 
 int /*<<< orphan*/  blk_add_trace_msg (scalar_t__,char*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_6__* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (TYPE_6__*) ; 
 int /*<<< orphan*/  md_bitmap_count_page (struct bitmap_counts*,int,int) ; 
 int /*<<< orphan*/  md_bitmap_file_clear_bit (struct bitmap*,int) ; 
 int* md_bitmap_get_counter (struct bitmap_counts*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_bitmap_set_pending (struct bitmap_counts*,int) ; 
 int /*<<< orphan*/  md_bitmap_wait_writes (struct bitmap*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_attr (struct bitmap*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_page_attr (struct bitmap*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_page_attr (struct bitmap*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_page (struct bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void md_bitmap_daemon_work(struct mddev *mddev)
{
	struct bitmap *bitmap;
	unsigned long j;
	unsigned long nextpage;
	sector_t blocks;
	struct bitmap_counts *counts;

	/* Use a mutex to guard daemon_work against
	 * bitmap_destroy.
	 */
	mutex_lock(&mddev->bitmap_info.mutex);
	bitmap = mddev->bitmap;
	if (bitmap == NULL) {
		mutex_unlock(&mddev->bitmap_info.mutex);
		return;
	}
	if (time_before(jiffies, bitmap->daemon_lastrun
			+ mddev->bitmap_info.daemon_sleep))
		goto done;

	bitmap->daemon_lastrun = jiffies;
	if (bitmap->allclean) {
		mddev->thread->timeout = MAX_SCHEDULE_TIMEOUT;
		goto done;
	}
	bitmap->allclean = 1;

	if (bitmap->mddev->queue)
		blk_add_trace_msg(bitmap->mddev->queue,
				  "md bitmap_daemon_work");

	/* Any file-page which is PENDING now needs to be written.
	 * So set NEEDWRITE now, then after we make any last-minute changes
	 * we will write it.
	 */
	for (j = 0; j < bitmap->storage.file_pages; j++)
		if (test_and_clear_page_attr(bitmap, j,
					     BITMAP_PAGE_PENDING))
			set_page_attr(bitmap, j,
				      BITMAP_PAGE_NEEDWRITE);

	if (bitmap->need_sync &&
	    mddev->bitmap_info.external == 0) {
		/* Arrange for superblock update as well as
		 * other changes */
		bitmap_super_t *sb;
		bitmap->need_sync = 0;
		if (bitmap->storage.filemap) {
			sb = kmap_atomic(bitmap->storage.sb_page);
			sb->events_cleared =
				cpu_to_le64(bitmap->events_cleared);
			kunmap_atomic(sb);
			set_page_attr(bitmap, 0,
				      BITMAP_PAGE_NEEDWRITE);
		}
	}
	/* Now look at the bitmap counters and if any are '2' or '1',
	 * decrement and handle accordingly.
	 */
	counts = &bitmap->counts;
	spin_lock_irq(&counts->lock);
	nextpage = 0;
	for (j = 0; j < counts->chunks; j++) {
		bitmap_counter_t *bmc;
		sector_t  block = (sector_t)j << counts->chunkshift;

		if (j == nextpage) {
			nextpage += PAGE_COUNTER_RATIO;
			if (!counts->bp[j >> PAGE_COUNTER_SHIFT].pending) {
				j |= PAGE_COUNTER_MASK;
				continue;
			}
			counts->bp[j >> PAGE_COUNTER_SHIFT].pending = 0;
		}

		bmc = md_bitmap_get_counter(counts, block, &blocks, 0);
		if (!bmc) {
			j |= PAGE_COUNTER_MASK;
			continue;
		}
		if (*bmc == 1 && !bitmap->need_sync) {
			/* We can clear the bit */
			*bmc = 0;
			md_bitmap_count_page(counts, block, -1);
			md_bitmap_file_clear_bit(bitmap, block);
		} else if (*bmc && *bmc <= 2) {
			*bmc = 1;
			md_bitmap_set_pending(counts, block);
			bitmap->allclean = 0;
		}
	}
	spin_unlock_irq(&counts->lock);

	md_bitmap_wait_writes(bitmap);
	/* Now start writeout on any page in NEEDWRITE that isn't DIRTY.
	 * DIRTY pages need to be written by bitmap_unplug so it can wait
	 * for them.
	 * If we find any DIRTY page we stop there and let bitmap_unplug
	 * handle all the rest.  This is important in the case where
	 * the first blocking holds the superblock and it has been updated.
	 * We mustn't write any other blocks before the superblock.
	 */
	for (j = 0;
	     j < bitmap->storage.file_pages
		     && !test_bit(BITMAP_STALE, &bitmap->flags);
	     j++) {
		if (test_page_attr(bitmap, j,
				   BITMAP_PAGE_DIRTY))
			/* bitmap_unplug will handle the rest */
			break;
		if (test_and_clear_page_attr(bitmap, j,
					     BITMAP_PAGE_NEEDWRITE)) {
			write_page(bitmap, bitmap->storage.filemap[j], 0);
		}
	}

 done:
	if (bitmap->allclean == 0)
		mddev->thread->timeout =
			mddev->bitmap_info.daemon_sleep;
	mutex_unlock(&mddev->bitmap_info.mutex);
}