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
struct ionic_queue {struct ionic_desc_info* tail; TYPE_3__* head; int /*<<< orphan*/  name; TYPE_2__* lif; } ;
struct ionic_desc_info {scalar_t__ index; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/  (* cb ) (struct ionic_queue*,struct ionic_desc_info*,struct ionic_cq_info*,void*) ;struct ionic_desc_info* next; } ;
struct ionic_cq_info {int dummy; } ;
typedef  int /*<<< orphan*/  (* ionic_desc_cb ) (struct ionic_queue*,struct ionic_desc_info*,struct ionic_cq_info*,void*) ;
struct TYPE_6__ {scalar_t__ index; } ;
struct TYPE_5__ {TYPE_1__* ionic; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ionic_q_is_posted (struct ionic_queue*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void ionic_q_service(struct ionic_queue *q, struct ionic_cq_info *cq_info,
		     unsigned int stop_index)
{
	struct ionic_desc_info *desc_info;
	ionic_desc_cb cb;
	void *cb_arg;

	/* check for empty queue */
	if (q->tail->index == q->head->index)
		return;

	/* stop index must be for a descriptor that is not yet completed */
	if (unlikely(!ionic_q_is_posted(q, stop_index)))
		dev_err(q->lif->ionic->dev,
			"ionic stop is not posted %s stop %u tail %u head %u\n",
			q->name, stop_index, q->tail->index, q->head->index);

	do {
		desc_info = q->tail;
		q->tail = desc_info->next;

		cb = desc_info->cb;
		cb_arg = desc_info->cb_arg;

		desc_info->cb = NULL;
		desc_info->cb_arg = NULL;

		if (cb)
			cb(q, desc_info, cq_info, cb_arg);
	} while (desc_info->index != stop_index);
}