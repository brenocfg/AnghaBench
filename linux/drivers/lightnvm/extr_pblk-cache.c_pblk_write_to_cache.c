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
struct request_queue {int dummy; } ;
struct pblk_w_ctx {unsigned long flags; scalar_t__ lba; int /*<<< orphan*/  ppa; } ;
struct pblk {TYPE_2__* disk; int /*<<< orphan*/  rl; int /*<<< orphan*/  req_writes; int /*<<< orphan*/  inflight_writes; int /*<<< orphan*/  user_wa; int /*<<< orphan*/  rwb; TYPE_1__* dev; } ;
struct bio {int bi_opf; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  part0; } ;
struct TYPE_3__ {struct request_queue* q; } ;

/* Variables and functions */
 int NVM_IO_DONE ; 
#define  NVM_IO_ERR 129 
#define  NVM_IO_REQUEUE 128 
 int /*<<< orphan*/  PBLK_EXPOSED_PAGE_SIZE ; 
 unsigned long PBLK_FLUSH_ENTRY ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PREFLUSH ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_advance (struct bio*,int /*<<< orphan*/ ) ; 
 void* bio_data (struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  generic_end_io_acct (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  generic_start_io_acct (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 unsigned long jiffies ; 
 scalar_t__ pblk_get_lba (struct bio*) ; 
 int pblk_get_secs (struct bio*) ; 
 int /*<<< orphan*/  pblk_pipeline_stop (struct pblk*) ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (int /*<<< orphan*/ *) ; 
 int pblk_rb_may_write_user (int /*<<< orphan*/ *,struct bio*,int,unsigned int*) ; 
 unsigned int pblk_rb_wrap_pos (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pblk_rb_write_entry_user (int /*<<< orphan*/ *,void*,struct pblk_w_ctx,unsigned int) ; 
 int /*<<< orphan*/  pblk_rl_inserted (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pblk_write_kick (struct pblk*) ; 
 int /*<<< orphan*/  pblk_write_should_kick (struct pblk*) ; 
 scalar_t__ unlikely (int) ; 

void pblk_write_to_cache(struct pblk *pblk, struct bio *bio,
				unsigned long flags)
{
	struct request_queue *q = pblk->dev->q;
	struct pblk_w_ctx w_ctx;
	sector_t lba = pblk_get_lba(bio);
	unsigned long start_time = jiffies;
	unsigned int bpos, pos;
	int nr_entries = pblk_get_secs(bio);
	int i, ret;

	generic_start_io_acct(q, REQ_OP_WRITE, bio_sectors(bio),
			      &pblk->disk->part0);

	/* Update the write buffer head (mem) with the entries that we can
	 * write. The write in itself cannot fail, so there is no need to
	 * rollback from here on.
	 */
retry:
	ret = pblk_rb_may_write_user(&pblk->rwb, bio, nr_entries, &bpos);
	switch (ret) {
	case NVM_IO_REQUEUE:
		io_schedule();
		goto retry;
	case NVM_IO_ERR:
		pblk_pipeline_stop(pblk);
		bio_io_error(bio);
		goto out;
	}

	pblk_ppa_set_empty(&w_ctx.ppa);
	w_ctx.flags = flags;
	if (bio->bi_opf & REQ_PREFLUSH) {
		w_ctx.flags |= PBLK_FLUSH_ENTRY;
		pblk_write_kick(pblk);
	}

	if (unlikely(!bio_has_data(bio)))
		goto out;

	for (i = 0; i < nr_entries; i++) {
		void *data = bio_data(bio);

		w_ctx.lba = lba + i;

		pos = pblk_rb_wrap_pos(&pblk->rwb, bpos + i);
		pblk_rb_write_entry_user(&pblk->rwb, data, w_ctx, pos);

		bio_advance(bio, PBLK_EXPOSED_PAGE_SIZE);
	}

	atomic64_add(nr_entries, &pblk->user_wa);

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_add(nr_entries, &pblk->inflight_writes);
	atomic_long_add(nr_entries, &pblk->req_writes);
#endif

	pblk_rl_inserted(&pblk->rl, nr_entries);

out:
	generic_end_io_acct(q, REQ_OP_WRITE, &pblk->disk->part0, start_time);
	pblk_write_should_kick(pblk);

	if (ret == NVM_IO_DONE)
		bio_endio(bio);
}