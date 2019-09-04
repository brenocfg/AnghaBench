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
struct pblk_sec_meta {int dummy; } ;
struct pblk_recov_alloc {void* dma_meta_list; void* dma_ppa_list; void* data; struct nvm_rq* rqd; struct pblk_sec_meta* meta_list; struct ppa_addr* ppa_list; } ;
struct pblk_line {int dummy; } ;
struct pblk {int /*<<< orphan*/  max_write_pgs; struct nvm_tgt_dev* dev; } ;
struct nvm_geo {int /*<<< orphan*/  csecs; } ;
struct nvm_tgt_dev {int /*<<< orphan*/  parent; struct nvm_geo geo; } ;
struct nvm_rq {int dummy; } ;
typedef  scalar_t__ meta_list ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PBLK_READ ; 
 void* kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct pblk_sec_meta* nvm_dev_dma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  nvm_dev_dma_free (int /*<<< orphan*/ ,struct pblk_sec_meta*,void*) ; 
 struct nvm_rq* pblk_alloc_rqd (struct pblk*,int /*<<< orphan*/ ) ; 
 scalar_t__ pblk_dma_meta_size ; 
 int /*<<< orphan*/  pblk_err (struct pblk*,char*) ; 
 scalar_t__ pblk_line_is_full (struct pblk_line*) ; 
 int /*<<< orphan*/  pblk_line_recov_close (struct pblk*,struct pblk_line*) ; 
 int pblk_recov_scan_all_oob (struct pblk*,struct pblk_line*,struct pblk_recov_alloc) ; 
 int pblk_recov_scan_oob (struct pblk*,struct pblk_line*,struct pblk_recov_alloc,int*) ; 

__attribute__((used)) static int pblk_recov_l2p_from_oob(struct pblk *pblk, struct pblk_line *line)
{
	struct nvm_tgt_dev *dev = pblk->dev;
	struct nvm_geo *geo = &dev->geo;
	struct nvm_rq *rqd;
	struct ppa_addr *ppa_list;
	struct pblk_sec_meta *meta_list;
	struct pblk_recov_alloc p;
	void *data;
	dma_addr_t dma_ppa_list, dma_meta_list;
	int done, ret = 0;

	meta_list = nvm_dev_dma_alloc(dev->parent, GFP_KERNEL, &dma_meta_list);
	if (!meta_list)
		return -ENOMEM;

	ppa_list = (void *)(meta_list) + pblk_dma_meta_size;
	dma_ppa_list = dma_meta_list + pblk_dma_meta_size;

	data = kcalloc(pblk->max_write_pgs, geo->csecs, GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto free_meta_list;
	}

	rqd = pblk_alloc_rqd(pblk, PBLK_READ);

	p.ppa_list = ppa_list;
	p.meta_list = meta_list;
	p.rqd = rqd;
	p.data = data;
	p.dma_ppa_list = dma_ppa_list;
	p.dma_meta_list = dma_meta_list;

	ret = pblk_recov_scan_oob(pblk, line, p, &done);
	if (ret) {
		pblk_err(pblk, "could not recover L2P from OOB\n");
		goto out;
	}

	if (!done) {
		ret = pblk_recov_scan_all_oob(pblk, line, p);
		if (ret) {
			pblk_err(pblk, "could not recover L2P from OOB\n");
			goto out;
		}
	}

	if (pblk_line_is_full(line))
		pblk_line_recov_close(pblk, line);

out:
	kfree(data);
free_meta_list:
	nvm_dev_dma_free(dev->parent, meta_list, dma_meta_list);

	return ret;
}