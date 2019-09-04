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
typedef  int /*<<< orphan*/  uint32_t ;
struct pp_hwmgr {int fan_ctrl_is_in_default_mode; int /*<<< orphan*/  device; void* tmin; void* fan_ctrl_default_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int /*<<< orphan*/  FDO_PWM_MODE ; 
 void* PHM_READ_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMIN ; 

int smu7_fan_ctrl_set_static_mode(struct pp_hwmgr *hwmgr, uint32_t mode)
{
	if (hwmgr->fan_ctrl_is_in_default_mode) {
		hwmgr->fan_ctrl_default_mode =
				PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
						CG_FDO_CTRL2, FDO_PWM_MODE);
		hwmgr->tmin =
				PHM_READ_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
						CG_FDO_CTRL2, TMIN);
		hwmgr->fan_ctrl_is_in_default_mode = false;
	}

	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, TMIN, 0);
	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, FDO_PWM_MODE, mode);

	return 0;
}