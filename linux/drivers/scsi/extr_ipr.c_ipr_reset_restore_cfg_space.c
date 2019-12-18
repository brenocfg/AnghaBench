#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int /*<<< orphan*/  endian_swap_reg; } ;
struct ipr_ioa_cfg {scalar_t__ sdt_state; scalar_t__ in_ioa_bringdown; scalar_t__ ioa_unit_checked; scalar_t__ sis64; TYPE_4__ regs; TYPE_6__* pdev; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_left; } ;
struct TYPE_7__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
struct TYPE_9__ {TYPE_2__ ioasa; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_5__ u; TYPE_3__ s; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_12__ {int state_saved; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 scalar_t__ GET_DUMP ; 
 int /*<<< orphan*/  IPR_DUMP_DELAY_TIMEOUT ; 
 int /*<<< orphan*/  IPR_ENDIAN_SWAP_KEY ; 
 int /*<<< orphan*/  IPR_IOASC_PCI_ACCESS_ERROR ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  IPR_WAIT_FOR_MAILBOX ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_dump_mailbox_wait ; 
 int /*<<< orphan*/  ipr_fail_all_ops (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_get_unit_check_buffer (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_ioa_bringdown_done ; 
 int /*<<< orphan*/  ipr_reset_alert ; 
 int /*<<< orphan*/  ipr_reset_enable_ioa ; 
 int /*<<< orphan*/  ipr_reset_get_unit_check_job ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipr_set_pcix_cmd_reg (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  pci_restore_state (TYPE_6__*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_reset_restore_cfg_space(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	u32 int_reg;

	ENTER;
	ioa_cfg->pdev->state_saved = true;
	pci_restore_state(ioa_cfg->pdev);

	if (ipr_set_pcix_cmd_reg(ioa_cfg)) {
		ipr_cmd->s.ioasa.hdr.ioasc = cpu_to_be32(IPR_IOASC_PCI_ACCESS_ERROR);
		return IPR_RC_JOB_CONTINUE;
	}

	ipr_fail_all_ops(ioa_cfg);

	if (ioa_cfg->sis64) {
		/* Set the adapter to the correct endian mode. */
		writel(IPR_ENDIAN_SWAP_KEY, ioa_cfg->regs.endian_swap_reg);
		int_reg = readl(ioa_cfg->regs.endian_swap_reg);
	}

	if (ioa_cfg->ioa_unit_checked) {
		if (ioa_cfg->sis64) {
			ipr_cmd->job_step = ipr_reset_get_unit_check_job;
			ipr_reset_start_timer(ipr_cmd, IPR_DUMP_DELAY_TIMEOUT);
			return IPR_RC_JOB_RETURN;
		} else {
			ioa_cfg->ioa_unit_checked = 0;
			ipr_get_unit_check_buffer(ioa_cfg);
			ipr_cmd->job_step = ipr_reset_alert;
			ipr_reset_start_timer(ipr_cmd, 0);
			return IPR_RC_JOB_RETURN;
		}
	}

	if (ioa_cfg->in_ioa_bringdown) {
		ipr_cmd->job_step = ipr_ioa_bringdown_done;
	} else if (ioa_cfg->sdt_state == GET_DUMP) {
		ipr_cmd->job_step = ipr_dump_mailbox_wait;
		ipr_cmd->u.time_left = IPR_WAIT_FOR_MAILBOX;
	} else {
		ipr_cmd->job_step = ipr_reset_enable_ioa;
	}

	LEAVE;
	return IPR_RC_JOB_CONTINUE;
}