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
struct pblk_w_ctx {int /*<<< orphan*/  bios; int /*<<< orphan*/  flags; } ;
struct pblk_rb {int /*<<< orphan*/  inflight_flush_point; } ;
struct pblk_c_ctx {int nr_valid; int sentry; scalar_t__ nr_padded; } ;
struct pblk {struct pblk_rb rwb; int /*<<< orphan*/  sync_writes; } ;
struct nvm_rq {int /*<<< orphan*/  bio; int /*<<< orphan*/  nr_ppas; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int PBLK_FLUSH_ENTRY ; 
 int /*<<< orphan*/  PBLK_WRITE ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_bio_free_pages (struct pblk*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 unsigned long pblk_rb_sync_advance (struct pblk_rb*,int) ; 
 struct pblk_w_ctx* pblk_rb_w_ctx (struct pblk_rb*,int) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static unsigned long pblk_end_w_bio(struct pblk *pblk, struct nvm_rq *rqd,
				    struct pblk_c_ctx *c_ctx)
{
	struct bio *original_bio;
	struct pblk_rb *rwb = &pblk->rwb;
	unsigned long ret;
	int i;

	for (i = 0; i < c_ctx->nr_valid; i++) {
		struct pblk_w_ctx *w_ctx;
		int pos = c_ctx->sentry + i;
		int flags;

		w_ctx = pblk_rb_w_ctx(rwb, pos);
		flags = READ_ONCE(w_ctx->flags);

		if (flags & PBLK_FLUSH_ENTRY) {
			flags &= ~PBLK_FLUSH_ENTRY;
			/* Release flags on context. Protect from writes */
			smp_store_release(&w_ctx->flags, flags);

#ifdef CONFIG_NVM_PBLK_DEBUG
			atomic_dec(&rwb->inflight_flush_point);
#endif
		}

		while ((original_bio = bio_list_pop(&w_ctx->bios)))
			bio_endio(original_bio);
	}

	if (c_ctx->nr_padded)
		pblk_bio_free_pages(pblk, rqd->bio, c_ctx->nr_valid,
							c_ctx->nr_padded);

#ifdef CONFIG_NVM_PBLK_DEBUG
	atomic_long_add(rqd->nr_ppas, &pblk->sync_writes);
#endif

	ret = pblk_rb_sync_advance(&pblk->rwb, c_ctx->nr_valid);

	bio_put(rqd->bio);
	pblk_free_rqd(pblk, rqd, PBLK_WRITE);

	return ret;
}