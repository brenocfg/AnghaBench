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
struct ipr_ioa_cfg {scalar_t__ ioa_unit_checked; } ;
struct ipr_cmnd {int /*<<< orphan*/  job_step; struct ipr_ioa_cfg* ioa_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER ; 
 int IPR_RC_JOB_RETURN ; 
 int /*<<< orphan*/  LEAVE ; 
 int /*<<< orphan*/  ipr_get_unit_check_buffer (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_reset_alert ; 
 int /*<<< orphan*/  ipr_reset_start_timer (struct ipr_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_reset_get_unit_check_job(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_ioa_cfg *ioa_cfg = ipr_cmd->ioa_cfg;

	ENTER;
	ioa_cfg->ioa_unit_checked = 0;
	ipr_get_unit_check_buffer(ioa_cfg);
	ipr_cmd->job_step = ipr_reset_alert;
	ipr_reset_start_timer(ipr_cmd, 0);

	LEAVE;
	return IPR_RC_JOB_RETURN;
}