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
typedef  int /*<<< orphan*/  u8 ;
struct cec_msg {int /*<<< orphan*/ * msg; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ CEC_LOG_ADDR_UNREGISTERED ; 
 int /*<<< orphan*/  CEC_MSG_FEATURE_ABORT ; 
 int /*<<< orphan*/  cec_msg_feature_abort (struct cec_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cec_msg_initiator (struct cec_msg*) ; 
 int /*<<< orphan*/  cec_msg_set_reply_to (struct cec_msg*,struct cec_msg*) ; 
 int cec_transmit_msg (struct cec_adapter*,struct cec_msg*,int) ; 

__attribute__((used)) static int cec_feature_abort_reason(struct cec_adapter *adap,
				    struct cec_msg *msg, u8 reason)
{
	struct cec_msg tx_msg = { };

	/*
	 * Don't reply with CEC_MSG_FEATURE_ABORT to a CEC_MSG_FEATURE_ABORT
	 * message!
	 */
	if (msg->msg[1] == CEC_MSG_FEATURE_ABORT)
		return 0;
	/* Don't Feature Abort messages from 'Unregistered' */
	if (cec_msg_initiator(msg) == CEC_LOG_ADDR_UNREGISTERED)
		return 0;
	cec_msg_set_reply_to(&tx_msg, msg);
	cec_msg_feature_abort(&tx_msg, msg->msg[1], reason);
	return cec_transmit_msg(adap, &tx_msg, false);
}