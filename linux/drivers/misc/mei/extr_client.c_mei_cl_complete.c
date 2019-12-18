#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mei_device {int /*<<< orphan*/  dev; } ;
struct mei_cl_cb {int fop_type; int /*<<< orphan*/  list; } ;
struct mei_cl {int /*<<< orphan*/  wait; int /*<<< orphan*/  rx_wait; int /*<<< orphan*/  rx_flow_ctrl_creds; int /*<<< orphan*/  rd_completed; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  writing_state; struct mei_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
#define  MEI_FOP_CONNECT 134 
#define  MEI_FOP_DISCONNECT 133 
#define  MEI_FOP_DISCONNECT_RSP 132 
#define  MEI_FOP_NOTIFY_START 131 
#define  MEI_FOP_NOTIFY_STOP 130 
#define  MEI_FOP_READ 129 
#define  MEI_FOP_WRITE 128 
 int /*<<< orphan*/  MEI_WRITE_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_cl_bus_rx_event (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_is_fixed_address (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_cl_set_disconnected (struct mei_cl*) ; 
 int /*<<< orphan*/  mei_io_cb_free (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  mei_tx_cb_dequeue (struct mei_cl_cb*) ; 
 int /*<<< orphan*/  pm_request_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void mei_cl_complete(struct mei_cl *cl, struct mei_cl_cb *cb)
{
	struct mei_device *dev = cl->dev;

	switch (cb->fop_type) {
	case MEI_FOP_WRITE:
		mei_tx_cb_dequeue(cb);
		cl->writing_state = MEI_WRITE_COMPLETE;
		if (waitqueue_active(&cl->tx_wait)) {
			wake_up_interruptible(&cl->tx_wait);
		} else {
			pm_runtime_mark_last_busy(dev->dev);
			pm_request_autosuspend(dev->dev);
		}
		break;

	case MEI_FOP_READ:
		list_add_tail(&cb->list, &cl->rd_completed);
		if (!mei_cl_is_fixed_address(cl) &&
		    !WARN_ON(!cl->rx_flow_ctrl_creds))
			cl->rx_flow_ctrl_creds--;
		if (!mei_cl_bus_rx_event(cl))
			wake_up_interruptible(&cl->rx_wait);
		break;

	case MEI_FOP_CONNECT:
	case MEI_FOP_DISCONNECT:
	case MEI_FOP_NOTIFY_STOP:
	case MEI_FOP_NOTIFY_START:
		if (waitqueue_active(&cl->wait))
			wake_up(&cl->wait);

		break;
	case MEI_FOP_DISCONNECT_RSP:
		mei_io_cb_free(cb);
		mei_cl_set_disconnected(cl);
		break;
	default:
		BUG_ON(0);
	}
}