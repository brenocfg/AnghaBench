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
struct be_queue_info {int created; int /*<<< orphan*/  id; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_q_destroy {int /*<<< orphan*/  id; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ETH ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_ETH_RX_DESTROY ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct be_cmd_req_q_destroy* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_rxq_destroy(struct be_adapter *adapter, struct be_queue_info *q)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_q_destroy *req;
	int status;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ETH,
			       OPCODE_ETH_RX_DESTROY, sizeof(*req), wrb, NULL);
	req->id = cpu_to_le16(q->id);

	status = be_mcc_notify_wait(adapter);
	q->created = false;

err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}