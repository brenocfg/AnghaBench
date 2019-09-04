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
typedef  int u32 ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_req_manage_iface_filters {int /*<<< orphan*/  target_iface_id; int /*<<< orphan*/  op; int /*<<< orphan*/  hdr; } ;
struct be_adapter {int /*<<< orphan*/  mcc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int EBUSY ; 
 int /*<<< orphan*/  OPCODE_COMMON_MANAGE_IFACE_FILTERS ; 
 int be_mcc_notify_wait (struct be_adapter*) ; 
 int /*<<< orphan*/  be_wrb_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct be_mcc_wrb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct be_cmd_req_manage_iface_filters* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mccq (struct be_adapter*) ; 

int be_cmd_manage_iface(struct be_adapter *adapter, u32 iface, u8 op)
{
	struct be_mcc_wrb *wrb;
	struct be_cmd_req_manage_iface_filters *req;
	int status;

	if (iface == 0xFFFFFFFF)
		return -1;

	mutex_lock(&adapter->mcc_lock);

	wrb = wrb_from_mccq(adapter);
	if (!wrb) {
		status = -EBUSY;
		goto err;
	}
	req = embedded_payload(wrb);

	be_wrb_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_COMMON,
			       OPCODE_COMMON_MANAGE_IFACE_FILTERS, sizeof(*req),
			       wrb, NULL);
	req->op = op;
	req->target_iface_id = cpu_to_le32(iface);

	status = be_mcc_notify_wait(adapter);
err:
	mutex_unlock(&adapter->mcc_lock);
	return status;
}