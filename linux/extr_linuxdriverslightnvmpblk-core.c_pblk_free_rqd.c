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
struct pblk_c_ctx {int /*<<< orphan*/  lun_bitmap; } ;
struct pblk {int /*<<< orphan*/  e_rq_pool; int /*<<< orphan*/  r_rq_pool; int /*<<< orphan*/  w_rq_pool; struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; } ;
struct nvm_rq {int /*<<< orphan*/  dma_meta_list; int /*<<< orphan*/  meta_list; } ;
typedef  int /*<<< orphan*/  mempool_t ;

/* Variables and functions */
#define  PBLK_ERASE 131 
#define  PBLK_READ 130 
#define  PBLK_WRITE 129 
#define  PBLK_WRITE_INT 128 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct nvm_rq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvm_rq_to_pdu (struct nvm_rq*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 

void pblk_free_rqd(struct pblk *pblk, struct nvm_rq *rqd, int type)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	mempool_t *pool;

	switch (type) {
	case PBLK_WRITE:
		kfree(((struct pblk_c_ctx *)nvm_rq_to_pdu(rqd))->lun_bitmap);
		/* fall through */
	case PBLK_WRITE_INT:
		pool = &pblk->w_rq_pool;
		break;
	case PBLK_READ:
		pool = &pblk->r_rq_pool;
		break;
	case PBLK_ERASE:
		pool = &pblk->e_rq_pool;
		break;
	default:
		pblk_err(pblk, "trying to free unknown rqd type\n");
		return;
	}

	if (rqd->meta_list)
		nvm_dev_dma_free(dev->parent, rqd->meta_list,
				rqd->dma_meta_list);
	mempool_free(rqd, pool);
}