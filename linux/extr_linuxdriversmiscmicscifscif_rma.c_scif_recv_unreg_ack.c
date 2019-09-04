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
struct scifmsg {scalar_t__* payload; } ;
struct scif_window {int /*<<< orphan*/  unregwq; int /*<<< orphan*/  unreg_state; scalar_t__ ep; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_COMPLETED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void scif_recv_unreg_ack(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_window *window =
		(struct scif_window *)msg->payload[1];
	struct scif_endpt *ep = (struct scif_endpt *)window->ep;

	mutex_lock(&ep->rma_info.rma_lock);
	window->unreg_state = OP_COMPLETED;
	wake_up(&window->unregwq);
	mutex_unlock(&ep->rma_info.rma_lock);
}