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
struct TYPE_4__ {int /*<<< orphan*/  time_left; } ;
struct ipr_cmnd {TYPE_2__ u; int /*<<< orphan*/  job_step; TYPE_1__* ioa_cfg; } ;
struct TYPE_3__ {scalar_t__ cfg_locked; } ;

/* Variables and functions */
 int IPR_RC_JOB_CONTINUE ; 
 int /*<<< orphan*/  IPR_WAIT_FOR_RESET_TIMEOUT ; 
 int /*<<< orphan*/  ipr_reset_block_config_access_wait ; 

__attribute__((used)) static int ipr_reset_block_config_access(struct ipr_cmnd *ipr_cmd)
{
	ipr_cmd->ioa_cfg->cfg_locked = 0;
	ipr_cmd->job_step = ipr_reset_block_config_access_wait;
	ipr_cmd->u.time_left = IPR_WAIT_FOR_RESET_TIMEOUT;
	return IPR_RC_JOB_CONTINUE;
}