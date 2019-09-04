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
typedef  size_t u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk_pad_rq {int /*<<< orphan*/  wait; int /*<<< orphan*/  ref; struct pblk* pblk; } ;
struct pblk_line {size_t cur_sec; int left_msecs; int id; int /*<<< orphan*/  blk_bitmap; int /*<<< orphan*/  lock; TYPE_1__* emeta; } ;
struct pblk {int min_write_pgs; int /*<<< orphan*/  max_write_pgs; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int csecs; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; struct nvm_geo geo; } ;
struct nvm_rq {int nr_ppas; struct ppa_addr* ppa_list; struct pblk_pad_rq* private; int /*<<< orphan*/  end_io; void* dma_meta_list; void* dma_ppa_list; struct pblk_sec_meta* meta_list; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; struct bio* bio; } ;
struct TYPE_4__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  scalar_t__ meta_list ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int ENOMEM ; 
 int ETIME ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 int /*<<< orphan*/  NVM_OP_PWRITE ; 
 int /*<<< orphan*/  PBLK_COMMAND_TIMEOUT_MS ; 
 int /*<<< orphan*/  PBLK_VMALLOC_META ; 
 int /*<<< orphan*/  PBLK_WRITE ; 
 int /*<<< orphan*/  PBLK_WRITE_INT ; 
 int PTR_ERR (struct bio*) ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,size_t,int) ; 
 int /*<<< orphan*/  array_size (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pblk_pad_rq*) ; 
 struct pblk_pad_rq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct pblk_sec_meta* nvm_dev_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,struct pblk_sec_meta*,void*) ; 
 size_t pblk_alloc_page (struct pblk*,struct pblk_line*,int) ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 struct bio* pblk_bio_map_addr (struct pblk*,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pblk_calc_secs (struct pblk*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_dma_meta_size ; 
 int /*<<< orphan*/  pblk_down_page (struct pblk*,struct ppa_addr*,int) ; 
 int /*<<< orphan*/  pblk_end_io_recov ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,...) ; 
 int /*<<< orphan*/  pblk_line_is_full (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_map_invalidate (struct pblk*,struct ppa_addr) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int /*<<< orphan*/  pblk_recov_complete ; 
 int /*<<< orphan*/  pblk_set_progr_mode (struct pblk*,int /*<<< orphan*/ ) ; 
 int pblk_submit_io (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_up_page (struct pblk*,struct ppa_addr*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_io_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pblk_recov_pad_oob(struct pblk *pblk, struct pblk_line *line,
			      int left_ppas)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct ppa_addr *ppa_list;
	struct pblk_sec_meta *meta_list;
	struct pblk_pad_rq *pad_rq;
	struct nvm_rq *rqd;
	struct bio *bio;
	void *data;
	dma_addr_t dma_ppa_list, dma_meta_list;
	__le64 *lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	u64 w_ptr = line->cur_sec;
	int left_line_ppas, rq_ppas, rq_len;
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
	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0);
	if (rq_ppas < pblk->min_write_pgs) {
		pblk_err(pblk, "corrupted pad line %d\n", line->id);
		goto fail_free_pad;
	}

	rq_len = rq_ppas * geo->csecs;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL, &dma_meta_list);
	if (!meta_list) {
		ret = -ENOMEM;
		goto fail_free_pad;
	}

	ppa_list = (void *)(meta_list) + pblk_dma_meta_size;
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size;

	bio = pblk_bio_map_addr(pblk, data, rq_ppas, rq_len,
						PBLK_VMALLOC_META, GFP_KERNEL);
	if (IS_ERR(bio)) {
		ret = PTR_ERR(bio);
		goto fail_free_meta;
	}

	bio->bi_iter.bi_sector = 0; /* internal bio */
	bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

	rqd = pblk_alloc_rqd(pblk, PBLK_WRITE_INT);

	rqd->bio = bio;
	rqd->opcode = NVM_OP_PWRITE;
	rqd->flags = pblk_set_progr_mode(pblk, PBLK_WRITE);
	rqd->meta_list = meta_list;
	rqd->nr_ppas = rq_ppas;
	rqd->ppa_list = ppa_list;
	rqd->dma_ppa_list = dma_ppa_list;
	rqd->dma_meta_list = dma_meta_list;
	rqd->end_io = pblk_end_io_recov;
	rqd->private = pad_rq;

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
			__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

			dev_ppa = addr_to_gen_ppa(pblk, w_ptr, line->id);

			pblk_map_invalidate(pblk, dev_ppa);
			lba_list[w_ptr] = meta_list[i].lba = addr_empty;
			rqd->ppa_list[i] = dev_ppa;
		}
	}

	kref_get(&pad_rq->ref);
	pblk_down_page(pblk, rqd->ppa_list, rqd->nr_ppas);

	ret = pblk_submit_io(pblk, rqd);
	if (ret) {
		pblk_err(pblk, "I/O submission failed: %d\n", ret);
		pblk_up_page(pblk, rqd->ppa_list, rqd->nr_ppas);
		goto fail_free_bio;
	}

	left_line_ppas -= rq_ppas;
	left_ppas -= rq_ppas;
	if (left_ppas && left_line_ppas)
		goto next_pad_rq;

	kref_put(&pad_rq->ref, pblk_recov_complete);

	if (!wait_for_completion_io_timeout(&pad_rq->wait,
				msecs_to_jiffies(PBLK_COMMAND_TIMEOUT_MS))) {
		pblk_err(pblk, "pad write timed out\n");
		ret = -ETIME;
	}

	if (!pblk_line_is_full(line))
		pblk_err(pblk, "corrupted padded line: %d\n", line->id);

	vfree(data);
free_rq:
	kfree(pad_rq);
	return ret;

fail_free_bio:
	bio_put(bio);
fail_free_meta:
	nvm_dev_dma_free(dev->parent, meta_list, dma_meta_list);
fail_free_pad:
	kfree(pad_rq);
	vfree(data);
	return ret;
}