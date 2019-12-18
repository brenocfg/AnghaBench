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
struct pblk_recov_alloc {void* dma_meta_list; void* dma_ppa_list; void* data; struct nvm_rq* rqd; void* meta_list; struct ppa_addr* ppa_list; } ;
struct pblk_line {int dummy; } ;
struct pblk {int /*<<< orphan*/  r_rq_pool; int /*<<< orphan*/  max_write_pgs; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int /*<<< orphan*/  csecs; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; struct nvm_geo geo; } ;
struct nvm_rq {int dummy; } ;
typedef  scalar_t__ meta_list ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct nvm_rq* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct nvm_rq*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nvm_dev_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ pblk_dma_meta_size (struct pblk*) ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 int /*<<< orphan*/  pblk_g_rq_size ; 
 scalar_t__ pblk_line_is_full (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_line_recov_close (struct pblk*,struct pblk_line*) ; 
 int pblk_recov_scan_oob (struct pblk*,struct pblk_line*,struct pblk_recov_alloc) ; 

__attribute__((used)) static int pblk_recov_l2p_from_oob(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct nvm_rq *rqd;
	struct ppa_addr *ppa_list;
	void *meta_list;
	struct pblk_recov_alloc p;
	void *data;
	dma_addr_t dma_ppa_list, dma_meta_list;
	int ret = 0;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL, &dma_meta_list);
	if (!meta_list)
		return -ENOMEM;

	ppa_list = (void *)(meta_list) + pblk_dma_meta_size(pblk);
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size(pblk);

	data = kcalloc(pblk->max_write_pgs, geo->csecs, GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto free_meta_list;
	}

	rqd = mempool_alloc(&pblk->r_rq_pool, GFP_KERNEL);
	memset(rqd, 0, pblk_g_rq_size);

	p.ppa_list = ppa_list;
	p.meta_list = meta_list;
	p.rqd = rqd;
	p.data = data;
	p.dma_ppa_list = dma_ppa_list;
	p.dma_meta_list = dma_meta_list;

	ret = pblk_recov_scan_oob(pblk, line, p);
	if (ret) {
		pblk_err(pblk, "could not recover L2P form OOB\n");
		goto out;
	}

	if (pblk_line_is_full(line))
		pblk_line_recov_close(pblk, line);

out:
	mempool_free(rqd, &pblk->r_rq_pool);
	kfree(data);
free_meta_list:
	nvm_dev_dma_free(dev->parent, meta_list, dma_meta_list);

	return ret;
}