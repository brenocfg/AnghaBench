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
typedef  scalar_t__ u8 ;
struct pmcraid_hostrcb {int /*<<< orphan*/ * cmd; } ;
struct pmcraid_instance {struct pmcraid_hostrcb ccn; struct pmcraid_hostrcb ldn; } ;
struct pmcraid_cmd {struct pmcraid_instance* drv_inst; } ;

/* Variables and functions */
 scalar_t__ PMCRAID_HCAM_CODE_LOG_DATA ; 
 int /*<<< orphan*/  PMCRAID_INTERNAL_TIMEOUT ; 
 int /*<<< orphan*/  pmcraid_prepare_cancel_cmd (struct pmcraid_cmd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcraid_send_cmd (struct pmcraid_cmd*,void (*) (struct pmcraid_cmd*),int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_timeout_handler ; 

__attribute__((used)) static void pmcraid_cancel_hcam(
	struct pmcraid_cmd *cmd,
	u8 type,
	void (*cmd_done) (struct pmcraid_cmd *)
)
{
	struct pmcraid_instance *pinstance;
	struct pmcraid_hostrcb  *hcam;

	pinstance = cmd->drv_inst;
	hcam =  (type == PMCRAID_HCAM_CODE_LOG_DATA) ?
		&pinstance->ldn : &pinstance->ccn;

	/* prepare for cancelling previous hcam command. If the HCAM is
	 * currently not pending with IOA, we would have hcam->cmd as non-null
	 */
	if (hcam->cmd == NULL)
		return;

	pmcraid_prepare_cancel_cmd(cmd, hcam->cmd);

	/* writing to IOARRIN must be protected by host_lock, as mid-layer
	 * schedule queuecommand while we are doing this
	 */
	pmcraid_send_cmd(cmd, cmd_done,
			 PMCRAID_INTERNAL_TIMEOUT,
			 pmcraid_timeout_handler);
}