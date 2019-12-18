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
typedef  int /*<<< orphan*/  uint16_t ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; } ;
struct beiscsi_hba {int /*<<< orphan*/  interface_handle; struct be_ctrl_info ctrl; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_set_vlan_req {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  interface_hndl; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_SET_VLAN ; 
 struct be_mcc_wrb* alloc_mcc_wrb (struct beiscsi_hba*,unsigned int*) ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_mcc_notify (struct beiscsi_hba*,unsigned int) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 struct be_cmd_set_vlan_req* embedded_payload (struct be_mcc_wrb*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int be_cmd_set_vlan(struct beiscsi_hba *phba,
		     uint16_t vlan_tag)
{
	unsigned int tag;
	struct be_mcc_wrb *wrb;
	struct be_cmd_set_vlan_req *req;
	struct be_ctrl_info *ctrl = &phba->ctrl;

	if (mutex_lock_interruptible(&ctrl->mbox_lock))
		return 0;
	wrb = alloc_mcc_wrb(phba, &tag);
	if (!wrb) {
		mutex_unlock(&ctrl->mbox_lock);
		return 0;
	}

	req = embedded_payload(wrb);
	be_wrb_hdr_prepare(wrb, sizeof(*wrb), true, 0);
	be_cmd_hdr_prepare(&req->hdr, CMD_SUBSYSTEM_ISCSI,
			   OPCODE_COMMON_ISCSI_NTWK_SET_VLAN,
			   sizeof(*req));

	req->interface_hndl = phba->interface_handle;
	req->vlan_priority = vlan_tag;

	be_mcc_notify(phba, tag);
	mutex_unlock(&ctrl->mbox_lock);

	return tag;
}