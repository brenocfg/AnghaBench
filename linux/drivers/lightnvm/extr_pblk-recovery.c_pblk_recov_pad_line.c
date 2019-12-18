#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk_pad_rq {int /*<<< orphan*/  wait; int /*<<< orphan*/  ref; struct pblk* pblk; } ;
struct pblk_line {size_t cur_sec; int left_msecs; int id; int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  lock; TYPE_1__* emeta; } ;
struct pblk {int min_write_pgs; int /*<<< orphan*/  max_write_pgs; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int /*<<< orphan*/  csecs; } ;
struct nvm_tgt_dev {struct nvm_geo geo; } ;
struct nvm_rq {int is_seq; int nr_ppas; void* meta_list; struct pblk_pad_rq* private; int /*<<< orphan*/  end_io; int /*<<< orphan*/  opcode; int /*<<< orphan*/ * bio; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVM_OP_PWRITE ; 
 int /*<<< orphan*/  PBLK_WRITE_INT ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,size_t,int) ; 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pblk_pad_rq*) ; 
 struct pblk_pad_rq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 size_t pblk_alloc_page (struct pblk*,struct pblk_line*,int) ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 int pblk_alloc_rqd_meta (struct pblk*,struct nvm_rq*) ; 
 int pblk_calc_secs (struct pblk*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pblk_down_chunk (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_end_io_recov ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_free_rqd (struct pblk*,struct nvm_rq*,int /*<<< orphan*/ ) ; 
 struct pblk_sec_meta* pblk_get_meta (struct pblk*,void*,int) ; 
 int /*<<< orphan*/  pblk_line_is_full (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_map_invalidate (struct pblk*,struct ppa_addr) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_recov_complete ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*,void*) ; 
 int /*<<< orphan*/  pblk_up_chunk (struct pblk*,struct ppa_addr) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pblk_recov_pad_line(struct pblk *pblk, struct pblk_line *line,
			       int left_ppas)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	void *meta_list;
	struct pblk_pad_rq *pad_rq;
	struct nvm_rq *rqd;
	struct ppa_addr *ppa_list;
	void *data;
	__le64 *lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	u64 w_ptr = line->cur_sec;
	int left_line_ppas, rq_ppas;
	int i, j;
	int ret = 0;

	spin_lock(&line->lock);
	left_line_ppas = line->left_msecs;
	spin_unlock(&line->lock);

	pad_rq = kmalloc(sizeof(struct pblk_pad_rq), GFP_KERNEL);
	if (!pad_rq)
		return -ENOMEM;

	data = vzalloc(array_size(pblk->max_write_pgs, geo->csecs));
	if (!data) {
		ret = -ENOMEM;
		goto free_rq;
	}

	pad_rq->pblk = pblk;
	init_completion(&pad_rq->wait);
	kref_init(&pad_rq->ref);

next_pad_rq:
	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0, false);
	if (rq_ppas < pblk->min_write_pgs) {
		pblk_err(pblk, "corrupted pad line %d\n", line->id);
		goto fail_complete;
	}

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE_INT);

	ret = pblk_alloc_rqd_meta(pblk, rqd);
	if (ret) {
		pblk_free_rqd(pblk, rqd, PBLK_WRITE_INT);
		goto fail_complete;
	}

	rqd->bio = NULL;
	rqd->opcode = NVM_OP_PWRITE;
	rqd->is_seq = 1;
	rqd->nr_ppas = rq_ppas;
	rqd->end_io = pblk_end_io_recov;
	rqd->private = pad_rq;

	ppa_list = nvm_rq_to_ppa_list(rqd);
	meta_list = rqd->meta_list;

	for (i = 0; i < rqd->nr_ppas; ) {
		struct ppa_addr ppa;
		int pos;

		w_ptr = pblk_alloc_page(pblk, line, pblk->min_write_pgs);
		ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);
		pos = pblk_ppa_to_pos(geo, ppa);

		while (test_bit(pos, line->blk_bitmap)) {
			w_ptr += pblk->min_write_pgs;
			ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);
			pos = pblk_ppa_to_pos(geo, ppa);
		}

		for (j = 0; j < pblk->min_write_pgs; j++, i++, w_ptr++) {
			struct ppa_addr dev_ppa;
			struct pblk_sec_meta *meta;
			__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

			dev_ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);

			pblk_map_invalidate(pblk, dev_ppa);
			lba_list[w_ptr] = addr_empty;
			meta = pblk_get_meta(pblk, meta_list, i);
			meta->lba = addr_empty;
			ppa_list[i] = dev_ppa;
		}
	}

	kref_get(&pad_rq->ref);
	pblk_down_chunk(pblk, ppa_list[0]);

	ret = pblk_submit_io(pblk, rqd, data);
	if (ret) {
		pblk_err(pblk, "I/O submission failed: %d\n", ret);
		pblk_up_chunk(pblk, ppa_list[0]);
		kref_put(&pad_rq->ref, pblk_recov_complete);
		pblk_free_rqd(pblk, rqd, PBLK_WRITE_INT);
		goto fail_complete;
	}

	left_line_ppas -= rq_ppas;
	left_ppas -= rq_ppas;
	if (left_ppas && left_line_ppas)
		goto next_pad_rq;

fail_complete:
	kref_put(&pad_rq->ref, pblk_recov_complete);
	wait_for_completion(&pad_rq->wait);

	if (!pblk_line_is_full(line))
		pblk_err(pblk, "corrupted padded line: %d\n", line->id);

	vfree(data);
free_rq:
	kfree(pad_rq);
	return ret;
}