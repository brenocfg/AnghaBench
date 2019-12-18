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
struct scifmsg {scalar_t__ uop; scalar_t__* payload; } ;
struct scif_fence_info {int dma_mark; int /*<<< orphan*/  comp; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_COMPLETED ; 
 int /*<<< orphan*/  OP_FAILED ; 
 scalar_t__ SCIF_MARK_ACK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void scif_recv_mark_resp(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];
	struct scif_fence_info *fence_req =
		(struct scif_fence_info *)msg->payload[1];

	mutex_lock(&ep->rma_info.rma_lock);
	if (msg->uop == SCIF_MARK_ACK) {
		fence_req->state = OP_COMPLETED;
		fence_req->dma_mark = (int)msg->payload[2];
	} else {
		fence_req->state = OP_FAILED;
	}
	mutex_unlock(&ep->rma_info.rma_lock);
	complete(&fence_req->comp);
}