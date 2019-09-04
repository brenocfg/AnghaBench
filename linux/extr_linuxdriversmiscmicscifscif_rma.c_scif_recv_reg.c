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
struct scif_window {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; int /*<<< orphan*/  remote_reg_list; } ;
struct scif_endpt {scalar_t__ state; int /*<<< orphan*/  remote_dev; TYPE_1__ rma_info; int /*<<< orphan*/  lock; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCIFEP_CONNECTED ; 
 scalar_t__ SCIF_REGISTER_ACK ; 
 scalar_t__ SCIF_REGISTER_NACK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_destroy_remote_lookup (int /*<<< orphan*/ ,struct scif_window*) ; 
 int /*<<< orphan*/  scif_destroy_remote_window (struct scif_window*) ; 
 int /*<<< orphan*/  scif_fixup_aper_base (int /*<<< orphan*/ ,struct scif_window*) ; 
 int /*<<< orphan*/  scif_insert_window (struct scif_window*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void scif_recv_reg(struct scif_dev *scifdev, struct scifmsg *msg)
{
	struct scif_endpt *ep = (struct scif_endpt *)msg->payload[0];
	struct scif_window *window =
		(struct scif_window *)msg->payload[1];

	mutex_lock(&ep->rma_info.rma_lock);
	spin_lock(&ep->lock);
	if (ep->state == SCIFEP_CONNECTED) {
		msg->uop = SCIF_REGISTER_ACK;
		scif_nodeqp_send(ep->remote_dev, msg);
		scif_fixup_aper_base(ep->remote_dev, window);
		/* No further failures expected. Insert new window */
		scif_insert_window(window, &ep->rma_info.remote_reg_list);
	} else {
		msg->uop = SCIF_REGISTER_NACK;
		scif_nodeqp_send(ep->remote_dev, msg);
	}
	spin_unlock(&ep->lock);
	mutex_unlock(&ep->rma_info.rma_lock);
	/* free up any lookup resources now that page lists are transferred */
	scif_destroy_remote_lookup(ep->remote_dev, window);
	/*
	 * We could not insert the window but we need to
	 * destroy the window.
	 */
	if (msg->uop == SCIF_REGISTER_NACK)
		scif_destroy_remote_window(window);
}