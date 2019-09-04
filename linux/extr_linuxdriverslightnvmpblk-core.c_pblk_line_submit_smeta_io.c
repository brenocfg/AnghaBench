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
struct pblk_sec_meta {int /*<<< orphan*/  lba; } ;
struct pblk_line_meta {int smeta_sec; int /*<<< orphan*/  smeta_len; } ;
struct pblk_line {int /*<<< orphan*/  id; int /*<<< orphan*/  smeta; TYPE_1__* emeta; } ;
struct pblk {int /*<<< orphan*/  inflight_io; struct pblk_line_meta lm; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; int /*<<< orphan*/  q; } ;
struct nvm_rq {int dma_meta_list; int dma_ppa_list; int opcode; int flags; int nr_ppas; struct pblk_sec_meta* meta_list; scalar_t__ error; struct pblk_sec_meta* ppa_list; struct bio* bio; } ;
struct TYPE_4__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bio*) ; 
 int NVM_OP_PREAD ; 
 int NVM_OP_PWRITE ; 
 int PBLK_READ ; 
 int PBLK_READ_RECOV ; 
 int /*<<< orphan*/  PBLK_READ_SEQUENTIAL ; 
 int PBLK_WRITE ; 
 int PTR_ERR (struct bio*) ; 
 int REQ_OP_READ ; 
 int REQ_OP_WRITE ; 
 struct pblk_sec_meta addr_to_gen_ppa (struct pblk*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct bio* bio_map_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emeta_to_lbas (struct pblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 struct pblk_sec_meta* nvm_dev_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,struct pblk_sec_meta*,int) ; 
 int pblk_dma_meta_size ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*,int) ; 
 int /*<<< orphan*/  pblk_log_read_err (struct pblk*,struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_log_write_err (struct pblk*,struct nvm_rq*) ; 
 int pblk_set_progr_mode (struct pblk*,int) ; 
 int pblk_set_read_mode (struct pblk*,int /*<<< orphan*/ ) ; 
 int pblk_submit_io_sync (struct pblk*,struct nvm_rq*) ; 

__attribute__((used)) static int pblk_line_submit_smeta_io(struct pblk *pblk, struct pblk_line *line,
				     u64 paddr, int dir)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct pblk_line_meta *lm = &pblk->lm;
	struct bio *bio;
	struct nvm_rq rqd;
	__le64 *lba_list = NULL;
	int i, ret;
	int cmd_op, bio_op;
	int flags;

	if (dir == PBLK_WRITE) {
		bio_op = REQ_OP_WRITE;
		cmd_op = NVM_OP_PWRITE;
		flags = pblk_set_progr_mode(pblk, PBLK_WRITE);
		lba_list = emeta_to_lbas(pblk, line->emeta->buf);
	} else if (dir == PBLK_READ_RECOV || dir == PBLK_READ) {
		bio_op = REQ_OP_READ;
		cmd_op = NVM_OP_PREAD;
		flags = pblk_set_read_mode(pblk, PBLK_READ_SEQUENTIAL);
	} else
		return -EINVAL;

	memset(&rqd, 0, sizeof(struct nvm_rq));

	rqd.meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL,
							&rqd.dma_meta_list);
	if (!rqd.meta_list)
		return -ENOMEM;

	rqd.ppa_list = rqd.meta_list + pblk_dma_meta_size;
	rqd.dma_ppa_list = rqd.dma_meta_list + pblk_dma_meta_size;

	bio = bio_map_kern(dev->q, line->smeta, lm->smeta_len, GFP_KERNEL);
	if (IS_ERR(bio)) {
		ret = PTR_ERR(bio);
		goto free_ppa_list;
	}

	bio->bi_iter.bi_sector = 0; /* internal bio */
	bio_set_op_attrs(bio, bio_op, 0);

	rqd.bio = bio;
	rqd.opcode = cmd_op;
	rqd.flags = flags;
	rqd.nr_ppas = lm->smeta_sec;

	for (i = 0; i < lm->smeta_sec; i++, paddr++) {
		struct pblk_sec_meta *meta_list = rqd.meta_list;

		rqd.ppa_list[i] = addr_to_gen_ppa(pblk, paddr, line->id);

		if (dir == PBLK_WRITE) {
			__le64 addr_empty = cpu_to_le64(ADDR_EMPTY);

			meta_list[i].lba = lba_list[paddr] = addr_empty;
		}
	}

	/*
	 * This I/O is sent by the write thread when a line is replace. Since
	 * the write thread is the only one sending write and erase commands,
	 * there is no need to take the LUN semaphore.
	 */
	ret = pblk_submit_io_sync(pblk, &rqd);
	if (ret) {
		pblk_err(pblk, "smeta I/O submission failed: %d\n", ret);
		bio_put(bio);
		goto free_ppa_list;
	}

	atomic_dec(&pblk->inflight_io);

	if (rqd.error) {
		if (dir == PBLK_WRITE) {
			pblk_log_write_err(pblk, &rqd);
			ret = 1;
		} else if (dir == PBLK_READ)
			pblk_log_read_err(pblk, &rqd);
	}

free_ppa_list:
	nvm_dev_dma_free(dev->parent, rqd.meta_list, rqd.dma_meta_list);

	return ret;
}