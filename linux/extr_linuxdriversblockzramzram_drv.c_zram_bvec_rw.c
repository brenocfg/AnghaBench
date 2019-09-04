#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  failed_writes; int /*<<< orphan*/  failed_reads; int /*<<< orphan*/  num_writes; int /*<<< orphan*/  num_reads; } ;
struct zram {TYPE_2__ stats; TYPE_1__* disk; } ;
struct request_queue {int dummy; } ;
struct bio_vec {int bv_len; int /*<<< orphan*/  bv_page; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  part0; struct request_queue* queue; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_end_io_acct (struct request_queue*,unsigned int,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  generic_start_io_acct (struct request_queue*,unsigned int,int,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  op_is_write (unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zram_accessed (struct zram*,int /*<<< orphan*/ ) ; 
 int zram_bvec_read (struct zram*,struct bio_vec*,int /*<<< orphan*/ ,int,struct bio*) ; 
 int zram_bvec_write (struct zram*,struct bio_vec*,int /*<<< orphan*/ ,int,struct bio*) ; 
 int /*<<< orphan*/  zram_slot_lock (struct zram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_slot_unlock (struct zram*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zram_bvec_rw(struct zram *zram, struct bio_vec *bvec, u32 index,
			int offset, unsigned int op, struct bio *bio)
{
	unsigned long start_time = jiffies;
	struct request_queue *q = zram->disk->queue;
	int ret;

	generic_start_io_acct(q, op, bvec->bv_len >> SECTOR_SHIFT,
			&zram->disk->part0);

	if (!op_is_write(op)) {
		atomic64_inc(&zram->stats.num_reads);
		ret = zram_bvec_read(zram, bvec, index, offset, bio);
		flush_dcache_page(bvec->bv_page);
	} else {
		atomic64_inc(&zram->stats.num_writes);
		ret = zram_bvec_write(zram, bvec, index, offset, bio);
	}

	generic_end_io_acct(q, op, &zram->disk->part0, start_time);

	zram_slot_lock(zram, index);
	zram_accessed(zram, index);
	zram_slot_unlock(zram, index);

	if (unlikely(ret < 0)) {
		if (!op_is_write(op))
			atomic64_inc(&zram->stats.failed_reads);
		else
			atomic64_inc(&zram->stats.failed_writes);
	}

	return ret;
}