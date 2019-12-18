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
struct pp_hwmgr {int dummy; } ;
typedef  enum SMU_ASIC_RESET_MODE { ____Placeholder_SMU_ASIC_RESET_MODE } SMU_ASIC_RESET_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_DeviceDriverReset ; 
 int smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smu10_asic_reset(struct pp_hwmgr *hwmgr, enum SMU_ASIC_RESET_MODE mode)
{
	return smum_send_msg_to_smc_with_parameter(hwmgr,
						   PPSMC_MSG_DeviceDriverReset,
						   mode);
}