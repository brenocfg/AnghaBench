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
struct scifmsg {int /*<<< orphan*/  uop; scalar_t__* payload; } ;
struct scif_remote_fence_info {int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;
struct TYPE_3__ {int /*<<< orphan*/  fence_refcount; } ;
struct scif_endpt {TYPE_1__ rma_info; int /*<<< orphan*/  remote_dev; scalar_t__ remote_ep; } ;
struct scif_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  misc_work; int /*<<< orphan*/  fencelock; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCIF_WAIT_NACK ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct scif_remote_fence_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct scifmsg*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 

void scif_recv_wait(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];
	struct scif_remote_fence_info *fence;

	/*
	 * Allocate structure for remote fence information and
	 * send a NACK if the allocation failed. The peer will
	 * return ENOMEM upon receiving a NACK.
	 */
	fence = kmalloc(sizeof(*fence), GFP_KERNEL);
	if (!fence) {
		msg->payload[0] = ep->remote_ep;
		msg->uop = SCIF_WAIT_NACK;
		scif_nodeqp_send(ep->remote_dev, msg);
		return;
	}

	/* Prepare the fence request */
	memcpy(&fence->msg, msg, sizeof(struct scifmsg));
	INIT_LIST_HEAD(&fence->list);

	/* Insert to the global remote fence request list */
	mutex_lock(&scif_info.fencelock);
	atomic_inc(&ep->rma_info.fence_refcount);
	list_add_tail(&fence->list, &scif_info.fence);
	mutex_unlock(&scif_info.fencelock);

	schedule_work(&scif_info.misc_work);
}