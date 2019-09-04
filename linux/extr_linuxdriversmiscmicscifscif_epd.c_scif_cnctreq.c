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
struct TYPE_4__ {size_t node; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct scifmsg {TYPE_2__ src; int /*<<< orphan*/  uop; TYPE_1__ dst; } ;
struct scif_endpt {scalar_t__ backlog; scalar_t__ conreqcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  conwq; int /*<<< orphan*/  conlist; } ;
struct scif_dev {int dummy; } ;
struct scif_conreq {int /*<<< orphan*/  list; struct scifmsg msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCIF_CNCT_REJ ; 
 int /*<<< orphan*/  kfree (struct scif_conreq*) ; 
 struct scif_conreq* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scif_dev ; 
 struct scif_endpt* scif_find_listen_ep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_nodeqp_send (int /*<<< orphan*/ *,struct scifmsg*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void scif_cnctreq(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = NULL;
	struct scif_conreq *conreq;

	conreq = kmalloc(sizeof(*conreq), GFP_KERNEL);
	if (!conreq)
		/* Lack of resources so reject the request. */
		goto conreq_sendrej;

	ep = scif_find_listen_ep(msg->dst.port);
	if (!ep)
		/*  Send reject due to no listening ports */
		goto conreq_sendrej_free;
	else
		spin_lock(&ep->lock);

	if (ep->backlog <= ep->conreqcnt) {
		/*  Send reject due to too many pending requests */
		spin_unlock(&ep->lock);
		goto conreq_sendrej_free;
	}

	conreq->msg = *msg;
	list_add_tail(&conreq->list, &ep->conlist);
	ep->conreqcnt++;
	wake_up_interruptible(&ep->conwq);
	spin_unlock(&ep->lock);
	return;

conreq_sendrej_free:
	kfree(conreq);
conreq_sendrej:
	msg->uop = SCIF_CNCT_REJ;
	scif_nodeqp_send(&scif_dev[msg->src.node], msg);
}