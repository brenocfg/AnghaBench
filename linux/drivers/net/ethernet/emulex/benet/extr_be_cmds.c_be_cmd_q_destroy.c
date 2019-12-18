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
struct be_queue_info {int created; int /*<<< orphan*/  id; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_q_destroy {int /*<<< orphan*/  id; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mbox_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int /*<<< orphan*/  OPCODE_COMMON_CQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_EQ_DESTROY ; 
 int /*<<< orphan*/  OPCODE_COMMON_MCC_DESTROY ; 
 int /*<<< orphan*/  OPCODE_ETH_RX_DESTROY ; 
 int /*<<< orphan*/  OPCODE_ETH_TX_DESTROY ; 
#define  QTYPE_CQ 132 
#define  QTYPE_EQ 131 
#define  QTYPE_MCCQ 130 
#define  QTYPE_RXQ 129 
#define  QTYPE_TXQ 128 
 int be_mbox_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct be_cmd_req_q_destroy* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (struct be_adapter*) ; 

int be_cmd_q_destroy(struct be_adapter *adapter, struct be_queue_info *q,
		     int queue_type)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_q_destroy *req;
	u8 subsys = 0, opcode = 0;
	int status;

	if (mutex_lock_interruptible(&adapter->mbox_lock))
		return -1;

	wrb = wrb_from_mbox(adapter);
	req = embedded_payload(wrb);

	switch (queue_type) {
	case QTYPE_EQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_EQ_DESTROY;
		break;
	case QTYPE_CQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_CQ_DESTROY;
		break;
	case QTYPE_TXQ:
		subsys = CMD_SUBSYSTEM_ETH;
		opcode = OPCODE_ETH_TX_DESTROY;
		break;
	case QTYPE_RXQ:
		subsys = CMD_SUBSYSTEM_ETH;
		opcode = OPCODE_ETH_RX_DESTROY;
		break;
	case QTYPE_MCCQ:
		subsys = CMD_SUBSYSTEM_COMMON;
		opcode = OPCODE_COMMON_MCC_DESTROY;
		break;
	default:
		BUG();
	}

	be_wrb_cmd_hdr_prepare(&req->hdr, subsys, opcode, sizeof(*req), wrb,
			       NULL);
	req->id = cpu_to_le16(q->id);

	status = be_mbox_notify_wait(adapter);
	q->created = false;

	mutex_unlock(&adapter->mbox_lock);
	return status;
}