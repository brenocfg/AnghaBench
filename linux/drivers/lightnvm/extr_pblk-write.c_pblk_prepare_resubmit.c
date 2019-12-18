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
struct ppa_addr {int dummy; } ;
struct pblk_w_ctx {scalar_t__ lba; int /*<<< orphan*/  ppa; int /*<<< orphan*/  flags; } ;
struct pblk_rb_entry {int /*<<< orphan*/  cacheline; struct pblk_w_ctx w_ctx; } ;
struct pblk_rb {struct pblk_rb_entry* entries; } ;
struct pblk_line {int /*<<< orphan*/  ref; int /*<<< orphan*/  sec_to_update; } ;
struct pblk {int /*<<< orphan*/  trans_lock; struct pblk_rb rwb; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 
 int PBLK_WRITTEN_DATA ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_line_put ; 
 int /*<<< orphan*/  pblk_ppa_comp (struct ppa_addr,int /*<<< orphan*/ ) ; 
 struct pblk_line* pblk_ppa_to_line (struct pblk*,int /*<<< orphan*/ ) ; 
 size_t pblk_rb_ptr_wrap (struct pblk_rb*,unsigned int,unsigned int) ; 
 struct ppa_addr pblk_trans_map_get (struct pblk*,scalar_t__) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pblk_prepare_resubmit(struct pblk *pblk, unsigned int sentry,
				  unsigned int nr_entries)
{
	struct pblk_rb *rb = &pblk->rwb;
	struct pblk_rb_entry *entry;
	struct pblk_line *line;
	struct pblk_w_ctx *w_ctx;
	struct ppa_addr ppa_l2p;
	int flags;
	unsigned int i;

	spin_lock(&pblk->trans_lock);
	for (i = 0; i < nr_entries; i++) {
		entry = &rb->entries[pblk_rb_ptr_wrap(rb, sentry, i)];
		w_ctx = &entry->w_ctx;

		/* Check if the lba has been overwritten */
		if (w_ctx->lba != ADDR_EMPTY) {
			ppa_l2p = pblk_trans_map_get(pblk, w_ctx->lba);
			if (!pblk_ppa_comp(ppa_l2p, entry->cacheline))
				w_ctx->lba = ADDR_EMPTY;
		}

		/* Mark up the entry as submittable again */
		flags = READ_ONCE(w_ctx->flags);
		flags |= PBLK_WRITTEN_DATA;
		/* Release flags on write context. Protect from writes */
		smp_store_release(&w_ctx->flags, flags);

		/* Decrease the reference count to the line as we will
		 * re-map these entries
		 */
		line = pblk_ppa_to_line(pblk, w_ctx->ppa);
		atomic_dec(&line->sec_to_update);
		kref_put(&line->ref, pblk_line_put);
	}
	spin_unlock(&pblk->trans_lock);
}