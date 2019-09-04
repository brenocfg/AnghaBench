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
struct TYPE_3__ {int ucTachometerPulsesPerRevolution; } ;
struct TYPE_4__ {TYPE_1__ fanInfo; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_2__ thermal_controller; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CG_FDO_CTRL2 ; 
 int /*<<< orphan*/  CG_TACH_CTRL ; 
 int /*<<< orphan*/  EDGE_PER_REV ; 
 int /*<<< orphan*/  PHM_WRITE_VFPF_INDIRECT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TACH_PWM_RESP_RATE ; 

__attribute__((used)) static int smu7_thermal_initialize(struct pp_hwmgr *hwmgr)
{
	if (hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution)
		PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_TACH_CTRL, EDGE_PER_REV,
				hwmgr->thermal_controller.fanInfo.
				ucTachometerPulsesPerRevolution - 1);

	PHM_WRITE_VFPF_INDIRECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, TACH_PWM_RESP_RATE, 0x28);

	return 0;
}