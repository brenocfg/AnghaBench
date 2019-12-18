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
struct TYPE_2__ {int pl; } ;
struct ppa_addr {TYPE_1__ g; } ;
struct nvm_geo {int pln_mode; } ;
struct nvm_tgt_dev {struct nvm_geo geo; struct nvm_dev* parent; } ;
struct nvm_rq {int nr_ppas; struct ppa_addr* ppa_list; int /*<<< orphan*/  dma_ppa_list; struct ppa_addr ppa_addr; } ;
struct nvm_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NVM_PLANE_SINGLE ; 
 struct ppa_addr* nvm_dev_dma_alloc (struct nvm_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int nvm_set_rqd_ppalist(struct nvm_tgt_dev *tgt_dev, struct nvm_rq *rqd,
			const struct ppa_addr *ppas, int nr_ppas)
{
	struct nvm_dev *dev = tgt_dev->parent;
	struct nvm_geo *geo = &tgt_dev->geo;
	int i, plane_cnt, pl_idx;
	struct ppa_addr ppa;

	if (geo->pln_mode == NVM_PLANE_SINGLE && nr_ppas == 1) {
		rqd->nr_ppas = nr_ppas;
		rqd->ppa_addr = ppas[0];

		return 0;
	}

	rqd->nr_ppas = nr_ppas;
	rqd->ppa_list = nvm_dev_dma_alloc(dev, GFP_KERNEL, &rqd->dma_ppa_list);
	if (!rqd->ppa_list) {
		pr_err("failed to allocate dma memory\n");
		return -ENOMEM;
	}

	plane_cnt = geo->pln_mode;
	rqd->nr_ppas *= plane_cnt;

	for (i = 0; i < nr_ppas; i++) {
		for (pl_idx = 0; pl_idx < plane_cnt; pl_idx++) {
			ppa = ppas[i];
			ppa.g.pl = pl_idx;
			rqd->ppa_list[(pl_idx * nr_ppas) + i] = ppa;
		}
	}

	return 0;
}