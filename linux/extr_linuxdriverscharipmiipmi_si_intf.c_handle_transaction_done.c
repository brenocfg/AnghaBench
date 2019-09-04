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
typedef  unsigned char u8 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  si_type; } ;
struct smi_info {int si_state; unsigned char msg_flags; struct ipmi_smi_msg* curr_msg; int /*<<< orphan*/  supports_event_msg_buff; TYPE_2__ io; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; } ;
struct ipmi_smi_msg {unsigned int rsp_size; unsigned char* rsp; int /*<<< orphan*/  (* done ) (struct ipmi_smi_msg*) ;} ;
struct TYPE_3__ {unsigned int (* get_result ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 unsigned char EVENT_MSG_BUFFER_FULL ; 
 unsigned char GLOBAL_ENABLES_MASK ; 
 int IPMI_MAX_MSG_LENGTH ; 
 int IPMI_NETFN_APP_REQUEST ; 
 unsigned char IPMI_SET_BMC_GLOBAL_ENABLES_CMD ; 
 unsigned char RECEIVE_MSG_AVAIL ; 
 int /*<<< orphan*/  SI_BT ; 
#define  SI_CHECKING_ENABLES 134 
#define  SI_CLEARING_FLAGS 133 
#define  SI_GETTING_EVENTS 132 
#define  SI_GETTING_FLAGS 131 
#define  SI_GETTING_MESSAGES 130 
#define  SI_NORMAL 129 
#define  SI_SETTING_ENABLES 128 
 int /*<<< orphan*/  check_bt_irq (struct smi_info*,int) ; 
 unsigned char current_global_enables (struct smi_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  debug_timestamp (char*) ; 
 int /*<<< orphan*/  deliver_recv_msg (struct smi_info*,struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  handle_flags (struct smi_info*) ; 
 int /*<<< orphan*/  incoming_messages ; 
 void* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  smi_inc_stat (struct smi_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_getting_events (struct smi_info*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned int stub10 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned int stub2 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned int stub3 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 unsigned int stub4 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub5 (struct ipmi_smi_msg*) ; 
 unsigned int stub6 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub7 (struct ipmi_smi_msg*) ; 
 unsigned int stub8 (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void handle_transaction_done(struct smi_info *smi_info)
{
	struct ipmi_smi_msg *msg;

	debug_timestamp("Done");
	switch (smi_info->si_state) {
	case SI_NORMAL:
		if (!smi_info->curr_msg)
			break;

		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here becase deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * time the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = NULL;
		deliver_recv_msg(smi_info, msg);
		break;

	case SI_GETTING_FLAGS:
	{
		unsigned char msg[4];
		unsigned int  len;

		/* We got the flags from the SMI, now handle them. */
		len = smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		if (msg[2] != 0) {
			/* Error fetching flags, just give up for now. */
			smi_info->si_state = SI_NORMAL;
		} else if (len < 4) {
			/*
			 * Hmm, no flags.  That's technically illegal, but
			 * don't use uninitialized data.
			 */
			smi_info->si_state = SI_NORMAL;
		} else {
			smi_info->msg_flags = msg[3];
			handle_flags(smi_info);
		}
		break;
	}

	case SI_CLEARING_FLAGS:
	{
		unsigned char msg[3];

		/* We cleared the flags. */
		smi_info->handlers->get_result(smi_info->si_sm, msg, 3);
		if (msg[2] != 0) {
			/* Error clearing flags */
			dev_warn(smi_info->io.dev,
				 "Error clearing flags: %2.2x\n", msg[2]);
		}
		smi_info->si_state = SI_NORMAL;
		break;
	}

	case SI_GETTING_EVENTS:
	{
		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here becase deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * time the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = NULL;
		if (msg->rsp[2] != 0) {
			/* Error getting event, probably done. */
			msg->done(msg);

			/* Take off the event flag. */
			smi_info->msg_flags &= ~EVENT_MSG_BUFFER_FULL;
			handle_flags(smi_info);
		} else {
			smi_inc_stat(smi_info, events);

			/*
			 * Do this before we deliver the message
			 * because delivering the message releases the
			 * lock and something else can mess with the
			 * state.
			 */
			handle_flags(smi_info);

			deliver_recv_msg(smi_info, msg);
		}
		break;
	}

	case SI_GETTING_MESSAGES:
	{
		smi_info->curr_msg->rsp_size
			= smi_info->handlers->get_result(
				smi_info->si_sm,
				smi_info->curr_msg->rsp,
				IPMI_MAX_MSG_LENGTH);

		/*
		 * Do this here becase deliver_recv_msg() releases the
		 * lock, and a new message can be put in during the
		 * time the lock is released.
		 */
		msg = smi_info->curr_msg;
		smi_info->curr_msg = NULL;
		if (msg->rsp[2] != 0) {
			/* Error getting event, probably done. */
			msg->done(msg);

			/* Take off the msg flag. */
			smi_info->msg_flags &= ~RECEIVE_MSG_AVAIL;
			handle_flags(smi_info);
		} else {
			smi_inc_stat(smi_info, incoming_messages);

			/*
			 * Do this before we deliver the message
			 * because delivering the message releases the
			 * lock and something else can mess with the
			 * state.
			 */
			handle_flags(smi_info);

			deliver_recv_msg(smi_info, msg);
		}
		break;
	}

	case SI_CHECKING_ENABLES:
	{
		unsigned char msg[4];
		u8 enables;
		bool irq_on;

		/* We got the flags from the SMI, now handle them. */
		smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		if (msg[2] != 0) {
			dev_warn(smi_info->io.dev,
				 "Couldn't get irq info: %x.\n", msg[2]);
			dev_warn(smi_info->io.dev,
				 "Maybe ok, but ipmi might run very slowly.\n");
			smi_info->si_state = SI_NORMAL;
			break;
		}
		enables = current_global_enables(smi_info, 0, &irq_on);
		if (smi_info->io.si_type == SI_BT)
			/* BT has its own interrupt enable bit. */
			check_bt_irq(smi_info, irq_on);
		if (enables != (msg[3] & GLOBAL_ENABLES_MASK)) {
			/* Enables are not correct, fix them. */
			msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
			msg[1] = IPMI_SET_BMC_GLOBAL_ENABLES_CMD;
			msg[2] = enables | (msg[3] & ~GLOBAL_ENABLES_MASK);
			smi_info->handlers->start_transaction(
				smi_info->si_sm, msg, 3);
			smi_info->si_state = SI_SETTING_ENABLES;
		} else if (smi_info->supports_event_msg_buff) {
			smi_info->curr_msg = ipmi_alloc_smi_msg();
			if (!smi_info->curr_msg) {
				smi_info->si_state = SI_NORMAL;
				break;
			}
			start_getting_events(smi_info);
		} else {
			smi_info->si_state = SI_NORMAL;
		}
		break;
	}

	case SI_SETTING_ENABLES:
	{
		unsigned char msg[4];

		smi_info->handlers->get_result(smi_info->si_sm, msg, 4);
		if (msg[2] != 0)
			dev_warn(smi_info->io.dev,
				 "Could not set the global enables: 0x%x.\n",
				 msg[2]);

		if (smi_info->supports_event_msg_buff) {
			smi_info->curr_msg = ipmi_alloc_smi_msg();
			if (!smi_info->curr_msg) {
				smi_info->si_state = SI_NORMAL;
				break;
			}
			start_getting_events(smi_info);
		} else {
			smi_info->si_state = SI_NORMAL;
		}
		break;
	}
	}
}