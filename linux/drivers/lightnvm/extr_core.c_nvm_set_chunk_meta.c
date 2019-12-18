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
struct ppa_addr {int dummy; } ;
struct nvm_tgt_dev {struct nvm_dev* parent; } ;
struct nvm_rq {int /*<<< orphan*/  nr_ppas; int /*<<< orphan*/  ppa_addr; } ;
struct TYPE_4__ {scalar_t__ version; } ;
struct nvm_dev {TYPE_1__* ops; TYPE_2__ geo; } ;
struct TYPE_3__ {int (* set_bb_tbl ) (struct nvm_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int NVM_MAX_VLBA ; 
 scalar_t__ NVM_OCSSD_SPEC_20 ; 
 int /*<<< orphan*/  memset (struct nvm_rq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvm_free_rqd_ppalist (struct nvm_tgt_dev*,struct nvm_rq*) ; 
 int /*<<< orphan*/  nvm_rq_tgt_to_dev (struct nvm_tgt_dev*,struct nvm_rq*) ; 
 int /*<<< orphan*/  nvm_set_rqd_ppalist (struct nvm_tgt_dev*,struct nvm_rq*,struct ppa_addr*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (struct nvm_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int nvm_set_chunk_meta(struct nvm_tgt_dev *tgt_dev, struct ppa_addr *ppas,
		       int nr_ppas, int type)
{
	struct nvm_dev *dev = tgt_dev->parent;
	struct nvm_rq rqd;
	int ret;

	if (dev->geo.version == NVM_OCSSD_SPEC_20)
		return 0;

	if (nr_ppas > NVM_MAX_VLBA) {
		pr_err("unable to update all blocks atomically\n");
		return -EINVAL;
	}

	memset(&rqd, 0, sizeof(struct nvm_rq));

	nvm_set_rqd_ppalist(tgt_dev, &rqd, ppas, nr_ppas);
	nvm_rq_tgt_to_dev(tgt_dev, &rqd);

	ret = dev->ops->set_bb_tbl(dev, &rqd.ppa_addr, rqd.nr_ppas, type);
	nvm_free_rqd_ppalist(tgt_dev, &rqd);
	if (ret)
		return -EINVAL;

	return 0;
}