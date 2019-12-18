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
struct vnic_wq {unsigned int index; } ;
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;
struct enic {int rq_count; int /*<<< orphan*/ * intr; int /*<<< orphan*/ * cq; struct vnic_wq* wq; struct napi_struct* napi; } ;

/* Variables and functions */
 unsigned int ENIC_WQ_NAPI_BUDGET ; 
 unsigned int enic_cq_wq (struct enic*,unsigned int) ; 
 unsigned int enic_msix_wq_intr (struct enic*,unsigned int) ; 
 int /*<<< orphan*/  enic_wq_service ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 unsigned int vnic_cq_service (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_intr_return_credits (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnic_intr_unmask (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enic_poll_msix_wq(struct napi_struct *napi, int budget)
{
	struct net_device *netdev = napi->dev;
	struct enic *enic = netdev_priv(netdev);
	unsigned int wq_index = (napi - &enic->napi[0]) - enic->rq_count;
	struct vnic_wq *wq = &enic->wq[wq_index];
	unsigned int cq;
	unsigned int intr;
	unsigned int wq_work_to_do = ENIC_WQ_NAPI_BUDGET;
	unsigned int wq_work_done;
	unsigned int wq_irq;

	wq_irq = wq->index;
	cq = enic_cq_wq(enic, wq_irq);
	intr = enic_msix_wq_intr(enic, wq_irq);
	wq_work_done = vnic_cq_service(&enic->cq[cq], wq_work_to_do,
				       enic_wq_service, NULL);

	vnic_intr_return_credits(&enic->intr[intr], wq_work_done,
				 0 /* don't unmask intr */,
				 1 /* reset intr timer */);
	if (!wq_work_done) {
		napi_complete(napi);
		vnic_intr_unmask(&enic->intr[intr]);
		return 0;
	}

	return budget;
}