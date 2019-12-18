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
typedef  scalar_t__ u64 ;
struct ppa_addr {int dummy; } ;
struct pblk_line_meta {int* emeta_sec; } ;
struct pblk_line {int id; int /*<<< orphan*/  blk_bitmap; scalar_t__ emeta_ssec; } ;
struct pblk {int min_write_pgs; int /*<<< orphan*/  inflight_io; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int csecs; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; struct nvm_geo geo; } ;
struct nvm_rq {int dma_meta_list; int dma_ppa_list; int nr_ppas; int is_seq; scalar_t__ error; void* meta_list; int /*<<< orphan*/  opcode; void* ppa_list; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVM_OP_PREAD ; 
 scalar_t__ NVM_RSP_WARN_HIGHECC ; 
 struct ppa_addr addr_to_gen_ppa (struct pblk*,scalar_t__,int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 void* nvm_dev_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,void*,int) ; 
 struct ppa_addr* nvm_rq_to_ppa_list (struct nvm_rq*) ; 
 scalar_t__ pblk_boundary_paddr_checks (struct pblk*,scalar_t__) ; 
 int pblk_calc_secs (struct pblk*,int,int /*<<< orphan*/ ,int) ; 
 int pblk_dma_meta_size (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 scalar_t__ pblk_io_aligned (struct pblk*,int) ; 
 int /*<<< orphan*/  pblk_log_read_err (struct pblk*,struct nvm_rq*) ; 
 int pblk_ppa_to_pos (struct nvm_geo*,struct ppa_addr) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*,void*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

int pblk_line_emeta_read(struct pblk *pblk, struct pblk_line *line,
			 void *emeta_buf)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct pblk_line_meta *lm = &pblk->lm;
	void *ppa_list_buf, *meta_list;
	struct ppa_addr *ppa_list;
	struct nvm_rq rqd;
	u64 paddr = line->emeta_ssec;
	dma_addr_t dma_ppa_list, dma_meta_list;
	int min = pblk->min_write_pgs;
	int left_ppas = lm->emeta_sec[0];
	int line_id = line->id;
	int rq_ppas, rq_len;
	int i, j;
	int ret;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL,
							&dma_meta_list);
	if (!meta_list)
		return -ENOMEM;

	ppa_list_buf = meta_list + pblk_dma_meta_size(pblk);
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size(pblk);

next_rq:
	memset(&rqd, 0, sizeof(struct nvm_rq));

	rq_ppas = pblk_calc_secs(pblk, left_ppas, 0, false);
	rq_len = rq_ppas * geo->csecs;

	rqd.meta_list = meta_list;
	rqd.ppa_list = ppa_list_buf;
	rqd.dma_meta_list = dma_meta_list;
	rqd.dma_ppa_list = dma_ppa_list;
	rqd.opcode = NVM_OP_PREAD;
	rqd.nr_ppas = rq_ppas;
	ppa_list = nvm_rq_to_ppa_list(&rqd);

	for (i = 0; i < rqd.nr_ppas; ) {
		struct ppa_addr ppa = addr_to_gen_ppa(pblk, paddr, line_id);
		int pos = pblk_ppa_to_pos(geo, ppa);

		if (pblk_io_aligned(pblk, rq_ppas))
			rqd.is_seq = 1;

		while (test_bit(pos, line->blk_bitmap)) {
			paddr += min;
			if (pblk_boundary_paddr_checks(pblk, paddr)) {
				ret = -EINTR;
				goto free_rqd_dma;
			}

			ppa = addr_to_gen_ppa(pblk, paddr, line_id);
			pos = pblk_ppa_to_pos(geo, ppa);
		}

		if (pblk_boundary_paddr_checks(pblk, paddr + min)) {
			ret = -EINTR;
			goto free_rqd_dma;
		}

		for (j = 0; j < min; j++, i++, paddr++)
			ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line_id);
	}

	ret = pblk_submit_io_sync(pblk, &rqd, emeta_buf);
	if (ret) {
		pblk_err(pblk, "emeta I/O submission failed: %d\n", ret);
		goto free_rqd_dma;
	}

	atomic_dec(&pblk->inflight_io);

	if (rqd.error && rqd.error != NVM_RSP_WARN_HIGHECC) {
		pblk_log_read_err(pblk, &rqd);
		ret = -EIO;
		goto free_rqd_dma;
	}

	emeta_buf += rq_len;
	left_ppas -= rq_ppas;
	if (left_ppas)
		goto next_rq;

free_rqd_dma:
	nvm_dev_dma_free(dev->parent, rqd.meta_list, rqd.dma_meta_list);
	return ret;
}