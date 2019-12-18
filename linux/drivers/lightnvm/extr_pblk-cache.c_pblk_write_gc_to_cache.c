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
struct pblk_w_ctx {scalar_t__ lba; int /*<<< orphan*/  ppa; int /*<<< orphan*/  flags; } ;
struct pblk_gc_rq {int secs_to_gc; int nr_secs; scalar_t__* lba_list; int /*<<< orphan*/ * paddr_list; int /*<<< orphan*/  line; void* data; } ;
struct pblk {int /*<<< orphan*/  recov_gc_writes; int /*<<< orphan*/  inflight_writes; int /*<<< orphan*/  gc_wa; int /*<<< orphan*/  rwb; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int NVM_IO_OK ; 
 int /*<<< orphan*/  PBLK_EXPOSED_PAGE_SIZE ; 
 int /*<<< orphan*/  PBLK_IOTYPE_GC ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_schedule () ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pblk_rb_may_write_gc (int /*<<< orphan*/ *,int,unsigned int*) ; 
 unsigned int pblk_rb_wrap_pos (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pblk_rb_write_entry_gc (int /*<<< orphan*/ *,void*,struct pblk_w_ctx,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pblk_write_should_kick (struct pblk*) ; 

int pblk_write_gc_to_cache(struct pblk *pblk, struct pblk_gc_rq *gc_rq)
{
	struct pblk_w_ctx w_ctx;
	unsigned int bpos, pos;
	void *data = gc_rq->data;
	int i, valid_entries;

	/* Update the write buffer head (mem) with the entries that we can
	 * write. The write in itself cannot fail, so there is no need to
	 * rollback from here on.
	 */
retry:
	if (!pblk_rb_may_write_gc(&pblk->rwb, gc_rq->secs_to_gc, &bpos)) {
		io_schedule();
		goto retry;
	}

	w_ctx.flags = PBLK_IOTYPE_GC;
	pblk_ppa_set_empty(&w_ctx.ppa);

	for (i = 0, valid_entries = 0; i < gc_rq->nr_secs; i++) {
		if (gc_rq->lba_list[i] == ADDR_EMPTY)
			continue;

		w_ctx.lba = gc_rq->lba_list[i];

		pos = pblk_rb_wrap_pos(&pblk->rwb, bpos + valid_entries);
		pblk_rb_write_entry_gc(&pblk->rwb, data, w_ctx, gc_rq->line,
						gc_rq->paddr_list[i], pos);

		data += PBLK_EXPOSED_PAGE_SIZE;
		valid_entries++;
	}

	WARN_ONCE(gc_rq->secs_to_gc != valid_entries,
					"pblk: inconsistent GC write\n");

	atomic64_add(valid_entries, &pblk->gc_wa);

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_add(valid_entries, &pblk->inflight_writes);
	atomic_long_add(valid_entries, &pblk->recov_gc_writes);
#endif

	pblk_write_should_kick(pblk);
	return NVM_IO_OK;
}