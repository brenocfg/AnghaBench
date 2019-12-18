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
struct cxd2880_tnrdmd_pid_ftr_cfg {int dummy; } ;
struct TYPE_2__ {scalar_t__ ts_output_if; } ;
struct cxd2880_tnrdmd {scalar_t__ diver_mode; scalar_t__ state; int pid_ftr_cfg_en; struct cxd2880_tnrdmd_pid_ftr_cfg pid_ftr_cfg; TYPE_1__ create_param; } ;

/* Variables and functions */
 scalar_t__ CXD2880_TNRDMD_DIVERMODE_SUB ; 
 scalar_t__ CXD2880_TNRDMD_STATE_ACTIVE ; 
 scalar_t__ CXD2880_TNRDMD_STATE_SLEEP ; 
 scalar_t__ CXD2880_TNRDMD_TSOUT_IF_TS ; 
 int EINVAL ; 
 int ENOTTY ; 
 int pid_ftr_setting (struct cxd2880_tnrdmd*,struct cxd2880_tnrdmd_pid_ftr_cfg*) ; 

int cxd2880_tnrdmd_set_pid_ftr(struct cxd2880_tnrdmd *tnr_dmd,
			       struct cxd2880_tnrdmd_pid_ftr_cfg
			       *pid_ftr_cfg)
{
	if (!tnr_dmd)
		return -EINVAL;

	if (tnr_dmd->diver_mode == CXD2880_TNRDMD_DIVERMODE_SUB)
		return -EINVAL;

	if (tnr_dmd->state != CXD2880_TNRDMD_STATE_SLEEP &&
	    tnr_dmd->state != CXD2880_TNRDMD_STATE_ACTIVE)
		return -EINVAL;

	if (tnr_dmd->create_param.ts_output_if == CXD2880_TNRDMD_TSOUT_IF_TS)
		return -ENOTTY;

	if (pid_ftr_cfg) {
		tnr_dmd->pid_ftr_cfg = *pid_ftr_cfg;
		tnr_dmd->pid_ftr_cfg_en = 1;
	} else {
		tnr_dmd->pid_ftr_cfg_en = 0;
	}

	if (tnr_dmd->state == CXD2880_TNRDMD_STATE_ACTIVE)
		return pid_ftr_setting(tnr_dmd, pid_ftr_cfg);
	else
		return 0;
}