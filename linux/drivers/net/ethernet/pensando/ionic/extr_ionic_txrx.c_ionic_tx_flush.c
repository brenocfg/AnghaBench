#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ionic_txq_comp {int /*<<< orphan*/  comp_index; int /*<<< orphan*/  color; } ;
struct ionic_queue {struct ionic_desc_info* tail; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;
struct ionic_desc_info {scalar_t__ index; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * cb; struct ionic_desc_info* next; } ;
struct ionic_cq {unsigned int num_descs; int done_color; TYPE_3__* bound_intr; TYPE_4__* tail; struct ionic_queue* bound_q; TYPE_2__* lif; } ;
struct TYPE_8__ {struct ionic_txq_comp* cq_desc; struct TYPE_8__* next; scalar_t__ last; } ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {TYPE_1__* ionic; } ;
struct TYPE_5__ {struct ionic_dev idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATS_CQE_CNT (struct ionic_cq*) ; 
 scalar_t__ color_match (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ionic_intr_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_tx_clean (struct ionic_queue*,struct ionic_desc_info*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

void ionic_tx_flush(struct ionic_cq *cq)
{
	struct ionic_txq_comp *comp = cq->tail->cq_desc;
	struct ionic_dev *idev = &cq->lif->ionic->idev;
	struct ionic_queue *q = cq->bound_q;
	struct ionic_desc_info *desc_info;
	unsigned int work_done = 0;

	/* walk the completed cq entries */
	while (work_done < cq->num_descs &&
	       color_match(comp->color, cq->done_color)) {

		/* clean the related q entries, there could be
		 * several q entries completed for each cq completion
		 */
		do {
			desc_info = q->tail;
			q->tail = desc_info->next;
			ionic_tx_clean(q, desc_info, cq->tail,
				       desc_info->cb_arg);
			desc_info->cb = NULL;
			desc_info->cb_arg = NULL;
		} while (desc_info->index != le16_to_cpu(comp->comp_index));

		if (cq->tail->last)
			cq->done_color = !cq->done_color;

		cq->tail = cq->tail->next;
		comp = cq->tail->cq_desc;
		DEBUG_STATS_CQE_CNT(cq);

		work_done++;
	}

	if (work_done)
		ionic_intr_credits(idev->intr_ctrl, cq->bound_intr->index,
				   work_done, 0);
}