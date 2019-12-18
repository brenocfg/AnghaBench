#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ionic_lif {TYPE_2__* notifyqcq; TYPE_1__* ionic; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;
struct ionic_cq {TYPE_3__* bound_intr; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {struct ionic_cq cq; } ;
struct TYPE_4__ {struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IONIC_INTR_CRED_RESET_COALESCE ; 
 int ionic_cq_service (struct ionic_cq*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_intr_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_notifyq_service ; 

__attribute__((used)) static int ionic_notifyq_clean(struct ionic_lif *lif, int budget)
{
	struct ionic_dev *idev = &lif->ionic->idev;
	struct ionic_cq *cq = &lif->notifyqcq->cq;
	u32 work_done;

	work_done = ionic_cq_service(cq, budget, ionic_notifyq_service,
				     NULL, NULL);
	if (work_done)
		ionic_intr_credits(idev->intr_ctrl, cq->bound_intr->index,
				   work_done, IONIC_INTR_CRED_RESET_COALESCE);

	return work_done;
}