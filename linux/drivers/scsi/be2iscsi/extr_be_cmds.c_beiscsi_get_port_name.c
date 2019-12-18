#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int phys_port; } ;
struct beiscsi_hba {int port_name; TYPE_3__ fw_config; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_ctrl_info {int /*<<< orphan*/  mbox_lock; int /*<<< orphan*/  mbox_mem; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {TYPE_4__ resp_hdr; int /*<<< orphan*/  req_hdr; } ;
struct TYPE_6__ {int port_names; } ;
struct TYPE_7__ {TYPE_1__ resp; } ;
struct be_cmd_get_port_name {TYPE_5__ h; TYPE_2__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_COMMON ; 
 int /*<<< orphan*/  EMBED_MBX_MAX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  OPCODE_COMMON_GET_PORT_NAME ; 
 int /*<<< orphan*/  be_cmd_hdr_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be_mbox_notify (struct be_ctrl_info*) ; 
 int /*<<< orphan*/  be_wrb_hdr_prepare (struct be_mcc_wrb*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct be_cmd_get_port_name* embedded_payload (struct be_mcc_wrb*) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct be_mcc_wrb* wrb_from_mbox (int /*<<< orphan*/ *) ; 

int beiscsi_get_port_name(struct be_ctrl_info *ctrl, struct beiscsi_hba *phba)
{
	int ret = 0;
	struct be_mcc_wrb *wrb;
	struct be_cmd_get_port_name *ioctl;

	mutex_lock(&ctrl->mbox_lock);
	wrb = wrb_from_mbox(&ctrl->mbox_mem);
	memset(wrb, 0, sizeof(*wrb));
	ioctl = embedded_payload(wrb);

	be_wrb_hdr_prepare(wrb, sizeof(*ioctl), true, 0);
	be_cmd_hdr_prepare(&ioctl->h.req_hdr, CMD_SUBSYSTEM_COMMON,
			   OPCODE_COMMON_GET_PORT_NAME,
			   EMBED_MBX_MAX_PAYLOAD_SIZE);
	ret = be_mbox_notify(ctrl);
	phba->port_name = 0;
	if (!ret) {
		phba->port_name = ioctl->p.resp.port_names >>
				  (phba->fw_config.phys_port * 8) & 0xff;
	} else {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_INIT,
			    "BG_%d : GET_PORT_NAME ret 0x%x status 0x%x\n",
			    ret, ioctl->h.resp_hdr.status);
	}

	if (phba->port_name == 0)
		phba->port_name = '?';

	mutex_unlock(&ctrl->mbox_lock);
	return ret;
}