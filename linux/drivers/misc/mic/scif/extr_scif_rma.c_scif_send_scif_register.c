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
typedef  void* u64 ;
struct scifmsg {void** payload; void* uop; int /*<<< orphan*/  src; } ;
struct TYPE_2__ {void* vaddr; } ;
struct scif_window {scalar_t__ reg_state; int /*<<< orphan*/  regwq; TYPE_1__ alloc_handle; } ;
struct scif_endpt {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  remote_dev; void* remote_ep; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOTCONN ; 
 scalar_t__ OP_FAILED ; 
 scalar_t__ OP_IN_PROGRESS ; 
 scalar_t__ SCIFEP_CONNECTED ; 
 void* SCIF_FREE_VIRT ; 
 int /*<<< orphan*/  SCIF_NODE_ALIVE_TIMEOUT ; 
 void* SCIF_REGISTER ; 
 int _scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 
 scalar_t__ scifdev_alive (struct scif_endpt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scif_send_scif_register(struct scif_endpt *ep,
				   struct scif_window *window)
{
	int err = 0;
	struct scifmsg msg;

	msg.src = ep->port;
	msg.payload[0] = ep->remote_ep;
	msg.payload[1] = window->alloc_handle.vaddr;
	msg.payload[2] = (u64)window;
	spin_lock(&ep->lock);
	if (ep->state == SCIFEP_CONNECTED) {
		msg.uop = SCIF_REGISTER;
		window->reg_state = OP_IN_PROGRESS;
		err = _scif_nodeqp_send(ep->remote_dev, &msg);
		spin_unlock(&ep->lock);
		if (!err) {
retry:
			/* Wait for a SCIF_REGISTER_(N)ACK message */
			err = wait_event_timeout(window->regwq,
						 window->reg_state !=
						 OP_IN_PROGRESS,
						 SCIF_NODE_ALIVE_TIMEOUT);
			if (!err && scifdev_alive(ep))
				goto retry;
			err = !err ? -ENODEV : 0;
			if (window->reg_state == OP_FAILED)
				err = -ENOTCONN;
		}
	} else {
		msg.uop = SCIF_FREE_VIRT;
		msg.payload[3] = SCIF_REGISTER;
		err = _scif_nodeqp_send(ep->remote_dev, &msg);
		spin_unlock(&ep->lock);
		if (!err)
			err = -ENOTCONN;
	}
	return err;
}