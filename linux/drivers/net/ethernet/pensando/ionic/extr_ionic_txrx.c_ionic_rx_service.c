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
struct ionic_rxq_comp {int /*<<< orphan*/  comp_index; int /*<<< orphan*/  pkt_type_color; } ;
struct ionic_queue {struct ionic_desc_info* tail; TYPE_1__* head; } ;
struct ionic_desc_info {scalar_t__ index; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * cb; struct ionic_desc_info* next; } ;
struct ionic_cq_info {struct ionic_rxq_comp* cq_desc; } ;
struct ionic_cq {int /*<<< orphan*/  done_color; struct ionic_queue* bound_q; } ;
struct TYPE_2__ {scalar_t__ index; } ;

/* Variables and functions */
 int /*<<< orphan*/  color_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_rx_clean (struct ionic_queue*,struct ionic_desc_info*,struct ionic_cq_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ionic_rx_service(struct ionic_cq *cq, struct ionic_cq_info *cq_info)
{
	struct ionic_rxq_comp *comp = cq_info->cq_desc;
	struct ionic_queue *q = cq->bound_q;
	struct ionic_desc_info *desc_info;

	if (!color_match(comp->pkt_type_color, cq->done_color))
		return false;

	/* check for empty queue */
	if (q->tail->index == q->head->index)
		return false;

	desc_info = q->tail;
	if (desc_info->index != le16_to_cpu(comp->comp_index))
		return false;

	q->tail = desc_info->next;

	/* clean the related q entry, only one per qc completion */
	ionic_rx_clean(q, desc_info, cq_info, desc_info->cb_arg);

	desc_info->cb = NULL;
	desc_info->cb_arg = NULL;

	return true;
}