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
struct ipr_ioa_cfg {int cfg_locked; TYPE_2__* pdev; int /*<<< orphan*/  reset; } ;
struct TYPE_3__ {scalar_t__ time_left; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; TYPE_1__ u; struct ipr_ioa_cfg* ioa_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IPR_CHECK_FOR_RESET_TIMEOUT ; 
 int IPR_RC_JOB_CONTINUE ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,scalar_t__) ; 
 scalar_t__ pci_cfg_access_trylock (TYPE_2__*) ; 

__attribute__((used)) static int ipr_reset_block_config_access_wait(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;
	int rc = IPR_RC_JOB_CONTINUE;

	if (pci_cfg_access_trylock(ioa_cfg->pdev)) {
		ioa_cfg->cfg_locked = 1;
		ipr_cmd->job_step = ioa_cfg->reset;
	} else {
		if (ipr_cmd->u.time_left) {
			rc = IPR_RC_JOB_RETURN;
			ipr_cmd->u.time_left -= IPR_CHECK_FOR_RESET_TIMEOUT;
			ipr_reset_start_timer(ipr_cmd,
					      IPR_CHECK_FOR_RESET_TIMEOUT);
		} else {
			ipr_cmd->job_step = ioa_cfg->reset;
			dev_err(&ioa_cfg->pdev->dev,
				"Timed out waiting to lock config access. Resetting anyway.\n");
		}
	}

	return rc;
}