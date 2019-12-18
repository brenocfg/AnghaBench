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
typedef  int u8 ;
struct se_cmd {scalar_t__ data_length; struct pscsi_plugin_task* priv; } ;
struct request {struct se_cmd* end_io_data; } ;
struct pscsi_plugin_task {int /*<<< orphan*/ * pscsi_cdb; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int result; scalar_t__ resid_len; int /*<<< orphan*/  sense; } ;

/* Variables and functions */
#define  DID_OK 128 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int host_byte (int) ; 
 int /*<<< orphan*/  kfree (struct pscsi_plugin_task*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct se_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pscsi_complete_cmd (struct se_cmd*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* scsi_req (struct request*) ; 
 int status_byte (int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_complete_cmd_with_length (struct se_cmd*,int,scalar_t__) ; 

__attribute__((used)) static void pscsi_req_done(struct request *req, blk_status_t status)
{
	struct se_cmd *cmd = req->end_io_data;
	struct pscsi_plugin_task *pt = cmd->priv;
	int result = scsi_req(req)->result;
	u8 scsi_status = status_byte(result) << 1;

	if (scsi_status) {
		pr_debug("PSCSI Status Byte exception at cmd: %p CDB:"
			" 0x%02x Result: 0x%08x\n", cmd, pt->pscsi_cdb[0],
			result);
	}

	pscsi_complete_cmd(cmd, scsi_status, scsi_req(req)->sense);

	switch (host_byte(result)) {
	case DID_OK:
		target_complete_cmd_with_length(cmd, scsi_status,
			cmd->data_length - scsi_req(req)->resid_len);
		break;
	default:
		pr_debug("PSCSI Host Byte exception at cmd: %p CDB:"
			" 0x%02x Result: 0x%08x\n", cmd, pt->pscsi_cdb[0],
			result);
		target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		break;
	}

	blk_put_request(req);
	kfree(pt);
}