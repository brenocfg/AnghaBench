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
typedef  int u64 ;
struct scifmsg {int uop; int* payload; int /*<<< orphan*/  src; } ;
struct scif_fence_info {scalar_t__ state; int dma_mark; int /*<<< orphan*/  comp; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; } ;
struct scif_endpt {int remote_ep; scalar_t__ state; TYPE_1__ rma_info; int /*<<< orphan*/  lock; int /*<<< orphan*/  remote_dev; int /*<<< orphan*/  port; } ;
typedef  scalar_t__ scif_epd_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OP_COMPLETED ; 
 scalar_t__ OP_FAILED ; 
 scalar_t__ OP_IN_PROGRESS ; 
 scalar_t__ SCIFEP_CONNECTED ; 
 int SCIF_MARK ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 int SCIF_REMOTE_FENCE ; 
 int SCIF_WAIT ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct scif_fence_info*) ; 
 struct scif_fence_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 
 scalar_t__ scifdev_alive (struct scif_endpt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _scif_send_fence(scif_epd_t epd, int uop, int mark, int *out_mark)
{
	int err;
	struct scifmsg msg;
	struct scif_fence_info *fence_req;
	struct scif_endpt *ep = (struct scif_endpt *)epd;

	fence_req = kmalloc(sizeof(*fence_req), GFP_KERNEL);
	if (!fence_req) {
		err = -ENOMEM;
		goto error;
	}

	fence_req->state = OP_IN_PROGRESS;
	init_completion(&fence_req->comp);

	msg.src = ep->port;
	msg.uop = uop;
	msg.payload[0] = ep->remote_ep;
	msg.payload[1] = (u64)fence_req;
	if (uop == SCIF_WAIT)
		msg.payload[2] = mark;
	spin_lock(&ep->lock);
	if (ep->state == SCIFEP_CONNECTED)
		err = scif_nodeqp_send(ep->remote_dev, &msg);
	else
		err = -ENOTCONN;
	spin_unlock(&ep->lock);
	if (err)
		goto error_free;
retry:
	/* Wait for a SCIF_WAIT_(N)ACK message */
	err = wait_for_completion_timeout(&fence_req->comp,
					  SCIF_NODE_ALIVE_TIMEOUT);
	if (!err && scifdev_alive(ep))
		goto retry;
	if (!err)
		err = -ENODEV;
	if (err > 0)
		err = 0;
	mutex_lock(&ep->rma_info.rma_lock);
	if (err < 0) {
		if (fence_req->state == OP_IN_PROGRESS)
			fence_req->state = OP_FAILED;
	}
	if (fence_req->state == OP_FAILED && !err)
		err = -ENOMEM;
	if (uop == SCIF_MARK && fence_req->state == OP_COMPLETED)
		*out_mark = SCIF_REMOTE_FENCE | fence_req->dma_mark;
	mutex_unlock(&ep->rma_info.rma_lock);
error_free:
	kfree(fence_req);
error:
	return err;
}