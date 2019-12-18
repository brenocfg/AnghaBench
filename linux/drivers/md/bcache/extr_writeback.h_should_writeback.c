#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; TYPE_3__* c; } ;
struct cached_dev {scalar_t__ partial_stripes_expensive; TYPE_4__ disk; } ;
struct TYPE_5__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {int bi_opf; TYPE_1__ bi_iter; } ;
struct TYPE_6__ {unsigned int in_use; } ;
struct TYPE_7__ {TYPE_2__ gc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_DETACHING ; 
 unsigned int CACHE_MODE_WRITEBACK ; 
 int REQ_META ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PRIO ; 
 scalar_t__ bcache_dev_stripe_dirty (struct cached_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bch_cutoff_writeback ; 
 unsigned int bch_cutoff_writeback_sync ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 scalar_t__ op_is_sync (int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool should_writeback(struct cached_dev *dc, struct bio *bio,
				    unsigned int cache_mode, bool would_skip)
{
	unsigned int in_use = dc->disk.c->gc_stats.in_use;

	if (cache_mode != CACHE_MODE_WRITEBACK ||
	    test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) ||
	    in_use > bch_cutoff_writeback_sync)
		return false;

	if (bio_op(bio) == REQ_OP_DISCARD)
		return false;

	if (dc->partial_stripes_expensive &&
	    bcache_dev_stripe_dirty(dc, bio->bi_iter.bi_sector,
				    bio_sectors(bio)))
		return true;

	if (would_skip)
		return false;

	return (op_is_sync(bio->bi_opf) ||
		bio->bi_opf & (REQ_META|REQ_PRIO) ||
		in_use <= bch_cutoff_writeback);
}