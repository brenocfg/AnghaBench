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
struct ipmi_smi_msg {int data_size; int* data; int rsp_size; int* rsp; int /*<<< orphan*/  link; int /*<<< orphan*/  msgid; int /*<<< orphan*/ * user_data; } ;
struct ipmi_smi {int run_to_completion; int /*<<< orphan*/  recv_tasklet; int /*<<< orphan*/  xmit_msgs_lock; struct ipmi_smi_msg* curr_msg; int /*<<< orphan*/  waiting_rcv_msgs_lock; int /*<<< orphan*/  waiting_rcv_msgs; int /*<<< orphan*/  channel_list; scalar_t__ in_shutdown; } ;
struct ipmi_channel {scalar_t__ medium; } ;
struct TYPE_2__ {struct ipmi_channel* c; } ;

/* Variables and functions */
 int IPMI_BUS_ERR ; 
 scalar_t__ IPMI_CHANNEL_MEDIUM_8023LAN ; 
 scalar_t__ IPMI_CHANNEL_MEDIUM_ASYNC ; 
 int IPMI_LOST_ARBITRATION_ERR ; 
 int IPMI_NAK_ON_WRITE_ERR ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_NODE_BUSY_ERR ; 
 int IPMI_SEND_MSG_CMD ; 
 TYPE_1__* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intf_err_seq (struct ipmi_smi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intf_start_seq_timer (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_free_smi_msg (struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  ipmi_inc_stat (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sent_ipmb_command_errs ; 
 int /*<<< orphan*/  sent_lan_command_errs ; 
 int /*<<< orphan*/  smi_recv_tasklet (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ipmi_smi_msg_received(struct ipmi_smi *intf,
			   struct ipmi_smi_msg *msg)
{
	unsigned long flags = 0; /* keep us warning-free. */
	int run_to_completion = intf->run_to_completion;

	if ((msg->data_size >= 2)
	    && (msg->data[0] == (IPMI_NETFN_APP_REQUEST << 2))
	    && (msg->data[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data == NULL)) {

		if (intf->in_shutdown)
			goto free_msg;

		/*
		 * This is the local response to a command send, start
		 * the timer for these.  The user_data will not be
		 * NULL if this is a response send, and we will let
		 * response sends just go through.
		 */

		/*
		 * Check for errors, if we get certain errors (ones
		 * that mean basically we can try again later), we
		 * ignore them and start the timer.  Otherwise we
		 * report the error immediately.
		 */
		if ((msg->rsp_size >= 3) && (msg->rsp[2] != 0)
		    && (msg->rsp[2] != IPMI_NODE_BUSY_ERR)
		    && (msg->rsp[2] != IPMI_LOST_ARBITRATION_ERR)
		    && (msg->rsp[2] != IPMI_BUS_ERR)
		    && (msg->rsp[2] != IPMI_NAK_ON_WRITE_ERR)) {
			int ch = msg->rsp[3] & 0xf;
			struct ipmi_channel *chans;

			/* Got an error sending the message, handle it. */

			chans = READ_ONCE(intf->channel_list)->c;
			if ((chans[ch].medium == IPMI_CHANNEL_MEDIUM_8023LAN)
			    || (chans[ch].medium == IPMI_CHANNEL_MEDIUM_ASYNC))
				ipmi_inc_stat(intf, sent_lan_command_errs);
			else
				ipmi_inc_stat(intf, sent_ipmb_command_errs);
			intf_err_seq(intf, msg->msgid, msg->rsp[2]);
		} else
			/* The message was sent, start the timer. */
			intf_start_seq_timer(intf, msg->msgid);

free_msg:
		ipmi_free_smi_msg(msg);
	} else {
		/*
		 * To preserve message order, we keep a queue and deliver from
		 * a tasklet.
		 */
		if (!run_to_completion)
			spin_lock_irqsave(&intf->waiting_rcv_msgs_lock, flags);
		list_add_tail(&msg->link, &intf->waiting_rcv_msgs);
		if (!run_to_completion)
			spin_unlock_irqrestore(&intf->waiting_rcv_msgs_lock,
					       flags);
	}

	if (!run_to_completion)
		spin_lock_irqsave(&intf->xmit_msgs_lock, flags);
	/*
	 * We can get an asynchronous event or receive message in addition
	 * to commands we send.
	 */
	if (msg == intf->curr_msg)
		intf->curr_msg = NULL;
	if (!run_to_completion)
		spin_unlock_irqrestore(&intf->xmit_msgs_lock, flags);

	if (run_to_completion)
		smi_recv_tasklet((unsigned long) intf);
	else
		tasklet_schedule(&intf->recv_tasklet);
}