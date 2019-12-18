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
struct se_cmd {int se_cmd_flags; scalar_t__ t_task_cdb; scalar_t__ __t_task_cdb; int /*<<< orphan*/  se_tmr_req; } ;

/* Variables and functions */
 int SCF_SCSI_TMR_CDB ; 
 int /*<<< orphan*/  core_tmr_release_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  transport_free_pages (struct se_cmd*) ; 

__attribute__((used)) static void target_free_cmd_mem(struct se_cmd *cmd)
{
	transport_free_pages(cmd);

	if (cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)
		core_tmr_release_req(cmd->se_tmr_req);
	if (cmd->t_task_cdb != cmd->__t_task_cdb)
		kfree(cmd->t_task_cdb);
}