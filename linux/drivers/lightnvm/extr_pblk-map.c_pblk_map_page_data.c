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
typedef  size_t u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_w_ctx {int /*<<< orphan*/  lba; struct ppa_addr ppa; } ;
struct pblk_sec_meta {void* lba; } ;
struct pblk_line {int /*<<< orphan*/  nr_valid_lbas; int /*<<< orphan*/  sec_to_update; int /*<<< orphan*/  ref; int /*<<< orphan*/  id; struct pblk_emeta* emeta; } ;
struct pblk_emeta {int /*<<< orphan*/  buf; } ;
struct pblk {int min_write_pgs; int /*<<< orphan*/  pad_wa; int /*<<< orphan*/  rwb; } ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int ENOSPC ; 
 int /*<<< orphan*/  __pblk_map_invalidate (struct pblk*,struct pblk_line*,size_t) ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__* emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 size_t pblk_alloc_page (struct pblk*,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_down_rq (struct pblk*,struct ppa_addr,unsigned long*) ; 
 struct pblk_sec_meta* pblk_get_meta (struct pblk*,void*,int) ; 
 int /*<<< orphan*/  pblk_line_close_meta (struct pblk*,struct pblk_line*) ; 
 struct pblk_line* pblk_line_get_data (struct pblk*) ; 
 scalar_t__ pblk_line_is_full (struct pblk_line*) ; 
 struct pblk_line* pblk_line_replace_data (struct pblk*) ; 
 int /*<<< orphan*/  pblk_pipeline_stop (struct pblk*) ; 
 struct pblk_w_ctx* pblk_rb_w_ctx (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int pblk_map_page_data(struct pblk *pblk, unsigned int sentry,
			      struct ppa_addr *ppa_list,
			      unsigned long *lun_bitmap,
			      void *meta_list,
			      unsigned int valid_secs)
{
	struct pblk_line *line = pblk_line_get_data(pblk);
	struct pblk_emeta *emeta;
	struct pblk_w_ctx *w_ctx;
	__le64 *lba_list;
	u64 paddr;
	int nr_secs = pblk->min_write_pgs;
	int i;

	if (!line)
		return -ENOSPC;

	if (pblk_line_is_full(line)) {
		struct pblk_line *prev_line = line;

		/* If we cannot allocate a new line, make sure to store metadata
		 * on current line and then fail
		 */
		line = pblk_line_replace_data(pblk);
		pblk_line_close_meta(pblk, prev_line);

		if (!line) {
			pblk_pipeline_stop(pblk);
			return -ENOSPC;
		}

	}

	emeta = line->emeta;
	lba_list = emeta_to_lbas(pblk, emeta->buf);

	paddr = pblk_alloc_page(pblk, line, nr_secs);

	for (i = 0; i < nr_secs; i++, paddr++) {
		struct pblk_sec_meta *meta = pblk_get_meta(pblk, meta_list, i);
		__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

		/* ppa to be sent to the device */
		ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);

		/* Write context for target bio completion on write buffer. Note
		 * that the write buffer is protected by the sync backpointer,
		 * and a single writer thread have access to each specific entry
		 * at a time. Thus, it is safe to modify the context for the
		 * entry we are setting up for submission without taking any
		 * lock or memory barrier.
		 */
		if (i < valid_secs) {
			kref_get(&line->ref);
			atomic_inc(&line->sec_to_update);
			w_ctx = pblk_rb_w_ctx(&pblk->rwb, sentry + i);
			w_ctx->ppa = ppa_list[i];
			meta->lba = cpu_to_le64(w_ctx->lba);
			lba_list[paddr] = cpu_to_le64(w_ctx->lba);
			if (lba_list[paddr] != addr_empty)
				line->nr_valid_lbas++;
			else
				atomic64_inc(&pblk->pad_wa);
		} else {
			lba_list[paddr] = addr_empty;
			meta->lba = addr_empty;
			__pblk_map_invalidate(pblk, line, paddr);
		}
	}

	pblk_down_rq(pblk, ppa_list[0], lun_bitmap);
	return 0;
}