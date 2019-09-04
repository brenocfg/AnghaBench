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
typedef  int /*<<< orphan*/  u8 ;
struct ocrdma_queue_info {int created; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;
struct ocrdma_dev {TYPE_1__ nic_info; struct ocrdma_delete_q_req* mbx_cmd; } ;
struct ocrdma_delete_q_req {int /*<<< orphan*/  id; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_CQ ; 
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_EQ ; 
 int /*<<< orphan*/  OCRDMA_CMD_DELETE_MQ ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
#define  QTYPE_CQ 130 
#define  QTYPE_EQ 129 
#define  QTYPE_MCCQ 128 
 int be_roce_mcc_cmd (int /*<<< orphan*/ ,struct ocrdma_delete_q_req*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ocrdma_delete_q_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_init_mch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ocrdma_mbx_delete_q(struct ocrdma_dev *dev,
			       struct ocrdma_queue_info *q, int queue_type)
{
	u8 opcode = 0;
	int status;
	struct ocrdma_delete_q_req *cmd = dev->mbx_cmd;

	switch (queue_type) {
	case QTYPE_MCCQ:
		opcode = OCRDMA_CMD_DELETE_MQ;
		break;
	case QTYPE_CQ:
		opcode = OCRDMA_CMD_DELETE_CQ;
		break;
	case QTYPE_EQ:
		opcode = OCRDMA_CMD_DELETE_EQ;
		break;
	default:
		BUG();
	}
	memset(cmd, 0, sizeof(*cmd));
	ocrdma_init_mch(&cmd->req, opcode, OCRDMA_SUBSYS_COMMON, sizeof(*cmd));
	cmd->id = q->id;

	status = be_roce_mcc_cmd(dev->nic_info.netdev,
				 cmd, sizeof(*cmd), NULL, NULL);
	if (!status)
		q->created = false;
	return status;
}