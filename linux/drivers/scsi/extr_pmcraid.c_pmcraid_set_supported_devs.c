#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_ioarcb {int /*<<< orphan*/ * cdb; int /*<<< orphan*/  request_type; int /*<<< orphan*/  resource_handle; } ;
struct pmcraid_cmd {int release; TYPE_1__* drv_inst; TYPE_2__* ioa_cb; } ;
struct TYPE_4__ {struct pmcraid_ioarcb ioarcb; } ;
struct TYPE_3__ {scalar_t__ reinit_cfg_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_DEVICES_SUPPORTED ; 
 int /*<<< orphan*/  PMCRAID_IOA_RES_HANDLE ; 
 int /*<<< orphan*/  PMCRAID_SET_SUPPORTED_DEVICES ; 
 int /*<<< orphan*/  PMCRAID_SET_SUP_DEV_TIMEOUT ; 
 int /*<<< orphan*/  REQ_TYPE_IOACMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void pmcraid_complete_ioa_reset (struct pmcraid_cmd*) ; 
 void pmcraid_reinit_cfgtable_done (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_reinit_cmdblk (struct pmcraid_cmd*) ; 
 int /*<<< orphan*/  pmcraid_send_cmd (struct pmcraid_cmd*,void (*) (struct pmcraid_cmd*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_timeout_handler ; 

__attribute__((used)) static void pmcraid_set_supported_devs(struct pmcraid_cmd *cmd)
{
	struct pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	void (*cmd_done) (struct pmcraid_cmd *) = pmcraid_complete_ioa_reset;

	pmcraid_reinit_cmdblk(cmd);

	ioarcb->resource_handle = cpu_to_le32(PMCRAID_IOA_RES_HANDLE);
	ioarcb->request_type = REQ_TYPE_IOACMD;
	ioarcb->cdb[0] = PMCRAID_SET_SUPPORTED_DEVICES;
	ioarcb->cdb[1] = ALL_DEVICES_SUPPORTED;

	/* If this was called as part of resource table reinitialization due to
	 * lost CCN, it is enough to return the command block back to free pool
	 * as part of set_supported_devs completion function.
	 */
	if (cmd->drv_inst->reinit_cfg_table) {
		cmd->drv_inst->reinit_cfg_table = 0;
		cmd->release = 1;
		cmd_done = pmcraid_reinit_cfgtable_done;
	}

	/* we will be done with the reset sequence after set supported devices,
	 * setup the done function to return the command block back to free
	 * pool
	 */
	pmcraid_send_cmd(cmd,
			 cmd_done,
			 PMCRAID_SET_SUP_DEV_TIMEOUT,
			 pmcraid_timeout_handler);
	return;
}