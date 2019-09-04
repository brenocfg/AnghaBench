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
struct nvm_tgt_dev {int dummy; } ;
struct nvm_rq {int nr_ppas; int /*<<< orphan*/ * ppa_list; int /*<<< orphan*/  ppa_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvm_ppa_tgt_to_dev (struct nvm_tgt_dev*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nvm_rq_tgt_to_dev(struct nvm_tgt_dev *tgt_dev, struct nvm_rq *rqd)
{
	if (rqd->nr_ppas == 1) {
		nvm_ppa_tgt_to_dev(tgt_dev, &rqd->ppa_addr, 1);
		return;
	}

	nvm_ppa_tgt_to_dev(tgt_dev, rqd->ppa_list, rqd->nr_ppas);
}