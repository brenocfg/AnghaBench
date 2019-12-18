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
typedef  union be_invalidate_connection_params {int dummy; } be_invalidate_connection_params ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {struct be_ctrl_info ctrl; } ;
struct beiscsi_endpoint {scalar_t__ conn; int /*<<< orphan*/  ep_cid; int /*<<< orphan*/  fw_handle; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_invalidate_connection_params_in {scalar_t__ save_cfg; int /*<<< orphan*/  cleanup_type; int /*<<< orphan*/  cid; int /*<<< orphan*/  session_handle; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_CLEANUP_TYPE_INVALIDATE ; 
 int /*<<< orphan*/  BE_CLEANUP_TYPE_ISSUE_TCP_RST ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI_INI ; 
 int /*<<< orphan*/  OPCODE_ISCSI_INI_DRIVER_INVALIDATE_CONNECTION ; 
 struct be_mcc_wrb* alloc_mcc_wrb (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct be_invalidate_connection_params_in* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

unsigned int beiscsi_invalidate_cxn(struct beiscsi_hba *phba,
				    struct beiscsi_endpoint *beiscsi_ep)
{
	struct be_invalidate_connection_params_in *req;
	struct be_ctrl_info *ctrl = &phba->ctrl;
	struct be_mcc_wrb *wrb;
	unsigned int tag = 0;

	mutex_lock(&ctrl->mbox_lock);
	wrb = alloc_mcc_wrb(phba, &tag);
	if (!wrb) {
		mutex_unlock(&ctrl->mbox_lock);
		return 0;
	}

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, sizeof(union be_invalidate_connection_params),
			   true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI_INI,
			   OPCODE_ISCSI_INI_DRIVER_INVALIDATE_CONNECTION,
			   sizeof(*req));
	req->session_handle = beiscsi_ep->fw_handle;
	req->cid = beiscsi_ep->ep_cid;
	if (beiscsi_ep->conn)
		req->cleanup_type = BE_CLEANUP_TYPE_INVALIDATE;
	else
		req->cleanup_type = BE_CLEANUP_TYPE_ISSUE_TCP_RST;
	/**
	 * 0 - non-persistent targets
	 * 1 - save session info on flash
	 */
	req->save_cfg = 0;
	be_mcc_notify(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);
	return tag;
}