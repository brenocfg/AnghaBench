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
typedef  int /*<<< orphan*/  u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line_mgmt {int /*<<< orphan*/  close_lock; } ;
struct pblk_line_meta {scalar_t__* emeta_len; } ;
struct pblk_line {int id; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; struct pblk_emeta* emeta; } ;
struct pblk_g_ctx {struct pblk_line* private; } ;
struct pblk_emeta {int mem; scalar_t__ buf; } ;
struct pblk {int min_write_pgs; struct pblk_line_meta lm; struct pblk_line_mgmt l_mg; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int csecs; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {int nr_ppas; } ;

/* Variables and functions */
 int NVM_IO_OK ; 
 int /*<<< orphan*/  PBLK_WRITE_INT ; 
 int /*<<< orphan*/  __pblk_alloc_page (struct pblk*,struct pblk_line*,int) ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct pblk_g_ctx* nvm_rq_to_pdu (struct nvm_rq*) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 int pblk_alloc_w_rq (struct pblk*,struct nvm_rq*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_dealloc_page (struct pblk*,struct pblk_line*,int) ; 
 int /*<<< orphan*/  pblk_down_chunk (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_end_io_write_meta ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*,void*) ; 
 int /*<<< orphan*/  pblk_up_chunk (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int pblk_submit_meta_io(struct pblk *pblk, struct pblk_line *meta_line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_mgmt *l_mg = &pblk->l_mg;
	struct pblk_line_meta *lm = &pblk->lm;
	struct pblk_emeta *emeta = meta_line->emeta;
	struct ppa_addr *ppa_list;
	struct pblk_g_ctx *m_ctx;
	struct nvm_rq *rqd;
	void *data;
	u64 paddr;
	int rq_ppas = pblk->min_write_pgs;
	int id = meta_line->id;
	int rq_len;
	int i, j;
	int ret;

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE_INT);

	m_ctx = nvm_rq_to_pdu(rqd);
	m_ctx->private = meta_line;

	rq_len = rq_ppas * geo->csecs;
	data = ((void *)emeta->buf) + emeta->mem;

	ret = pblk_alloc_w_rq(pblk, rqd, rq_ppas, pblk_end_io_write_meta);
	if (ret)
		goto fail_free_rqd;

	ppa_list = nvm_rq_to_ppa_list(rqd);
	for (i = 0; i < rqd->nr_ppas; ) {
		spin_lock(&meta_line->lock);
		paddr = __pblk_alloc_page(pblk, meta_line, rq_ppas);
		spin_unlock(&meta_line->lock);
		for (j = 0; j < rq_ppas; j++, i++, paddr++)
			ppa_list[i] = addr_to_gen_ppa(pblk, paddr, id);
	}

	spin_lock(&l_mg->close_lock);
	emeta->mem += rq_len;
	if (emeta->mem >= lm->emeta_len[0])
		list_del(&meta_line->list);
	spin_unlock(&l_mg->close_lock);

	pblk_down_chunk(pblk, ppa_list[0]);

	ret = pblk_submit_io(pblk, rqd, data);
	if (ret) {
		pblk_err(pblk, "emeta I/O submission failed: %d\n", ret);
		goto fail_rollback;
	}

	return NVM_IO_OK;

fail_rollback:
	pblk_up_chunk(pblk, ppa_list[0]);
	spin_lock(&l_mg->close_lock);
	pblk_dealloc_page(pblk, meta_line, rq_ppas);
	list_add(&meta_line->list, &meta_line->list);
	spin_unlock(&l_mg->close_lock);
fail_free_rqd:
	pblk_free_rqd(pblk, rqd, PBLK_WRITE_INT);
	return ret;
}