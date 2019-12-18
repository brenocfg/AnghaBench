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
struct pblk {struct nvm_tgt_dev* dev; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; } ;
struct nvm_rq {int /*<<< orphan*/  dma_meta_list; int /*<<< orphan*/  meta_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pblk_free_rqd_meta(struct pblk *pblk, struct nvm_rq *rqd)
{
	struct nvm_tgt_dev *dev = pblk->dev;

	if (rqd->meta_list)
		nvm_dev_dma_free(dev->parent, rqd->meta_list,
				rqd->dma_meta_list);
}