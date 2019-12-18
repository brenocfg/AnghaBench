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
struct ibmvmc_crq_msg {int type; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
#define  VMC_MSG_ADD_BUF 138 
#define  VMC_MSG_ADD_BUF_RESP 137 
#define  VMC_MSG_CAP 136 
#define  VMC_MSG_CAP_RESP 135 
#define  VMC_MSG_CLOSE 134 
#define  VMC_MSG_CLOSE_RESP 133 
#define  VMC_MSG_OPEN 132 
#define  VMC_MSG_OPEN_RESP 131 
#define  VMC_MSG_REM_BUF 130 
#define  VMC_MSG_REM_BUF_RESP 129 
#define  VMC_MSG_SIGNAL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ ibmvmc ; 
 int /*<<< orphan*/  ibmvmc_add_buffer (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 
 int /*<<< orphan*/  ibmvmc_process_capabilities (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 
 int /*<<< orphan*/  ibmvmc_process_close_resp (struct ibmvmc_crq_msg*,struct crq_server_adapter*) ; 
 int /*<<< orphan*/  ibmvmc_process_open_resp (struct ibmvmc_crq_msg*,struct crq_server_adapter*) ; 
 int /*<<< orphan*/  ibmvmc_recv_msg (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 
 int /*<<< orphan*/  ibmvmc_rem_buffer (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 
 int ibmvmc_state_capabilities ; 
 int /*<<< orphan*/  ibmvmc_validate_hmc_session (struct crq_server_adapter*,struct ibmvmc_crq_msg*) ; 

__attribute__((used)) static void ibmvmc_crq_process(struct crq_server_adapter *adapter,
			       struct ibmvmc_crq_msg *crq)
{
	switch (crq->type) {
	case VMC_MSG_CAP_RESP:
		dev_dbg(adapter->dev, "CRQ recv: capabilities resp (0x%x)\n",
			crq->type);
		if (ibmvmc.state == ibmvmc_state_capabilities)
			ibmvmc_process_capabilities(adapter, crq);
		else
			dev_warn(adapter->dev, "caps msg invalid in state 0x%x\n",
				 ibmvmc.state);
		break;
	case VMC_MSG_OPEN_RESP:
		dev_dbg(adapter->dev, "CRQ recv: open resp (0x%x)\n",
			crq->type);
		if (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_process_open_resp(crq, adapter);
		break;
	case VMC_MSG_ADD_BUF:
		dev_dbg(adapter->dev, "CRQ recv: add buf (0x%x)\n",
			crq->type);
		if (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_add_buffer(adapter, crq);
		break;
	case VMC_MSG_REM_BUF:
		dev_dbg(adapter->dev, "CRQ recv: rem buf (0x%x)\n",
			crq->type);
		if (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_rem_buffer(adapter, crq);
		break;
	case VMC_MSG_SIGNAL:
		dev_dbg(adapter->dev, "CRQ recv: signal msg (0x%x)\n",
			crq->type);
		if (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_recv_msg(adapter, crq);
		break;
	case VMC_MSG_CLOSE_RESP:
		dev_dbg(adapter->dev, "CRQ recv: close resp (0x%x)\n",
			crq->type);
		if (ibmvmc_validate_hmc_session(adapter, crq) == 0)
			ibmvmc_process_close_resp(crq, adapter);
		break;
	case VMC_MSG_CAP:
	case VMC_MSG_OPEN:
	case VMC_MSG_CLOSE:
	case VMC_MSG_ADD_BUF_RESP:
	case VMC_MSG_REM_BUF_RESP:
		dev_warn(adapter->dev, "CRQ recv: unexpected msg (0x%x)\n",
			 crq->type);
		break;
	default:
		dev_warn(adapter->dev, "CRQ recv: unknown msg (0x%x)\n",
			 crq->type);
		break;
	}
}