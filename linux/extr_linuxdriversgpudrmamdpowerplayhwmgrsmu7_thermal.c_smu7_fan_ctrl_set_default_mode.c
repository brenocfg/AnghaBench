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
struct pp_hwmgr {int fan_ctrl_is_in_default_mode; int /*<<< orphan*/  tmin; int /*<<< orphan*/  device; int /*<<< orphan*/  fan_ctrl_default_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int /*<<< orphan*/  FDO_PWM_MODE ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMIN ; 

int smu7_fan_ctrl_set_default_mode(struct pp_hwmgr *hwmgr)
{
	if (!hwmgr->fan_ctrl_is_in_default_mode) {
		PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_FDO_CTRL2, FDO_PWM_MODE, hwmgr->fan_ctrl_default_mode);
		PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_FDO_CTRL2, TMIN, hwmgr->tmin);
		hwmgr->fan_ctrl_is_in_default_mode = true;
	}

	return 0;
}