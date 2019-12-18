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
struct ionic_queue {int dbval; TYPE_2__* head; int /*<<< orphan*/  hw_type; int /*<<< orphan*/  hw_index; int /*<<< orphan*/  name; struct ionic_lif* lif; } ;
struct ionic_lif {int /*<<< orphan*/  kern_dbpage; int /*<<< orphan*/  index; TYPE_1__* ionic; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ionic_desc_cb ;
struct TYPE_4__ {int index; struct TYPE_4__* next; void* cb_arg; int /*<<< orphan*/  cb; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ionic_dbell_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ionic_q_post(struct ionic_queue *q, bool ring_doorbell, ionic_desc_cb cb,
		  void *cb_arg)
{
	struct device *dev = q->lif->ionic->dev;
	struct ionic_lif *lif = q->lif;

	q->head->cb = cb;
	q->head->cb_arg = cb_arg;
	q->head = q->head->next;

	dev_dbg(dev, "lif=%d qname=%s qid=%d qtype=%d p_index=%d ringdb=%d\n",
		q->lif->index, q->name, q->hw_type, q->hw_index,
		q->head->index, ring_doorbell);

	if (ring_doorbell)
		ionic_dbell_ring(lif->kern_dbpage, q->hw_type,
				 q->dbval | q->head->index);
}