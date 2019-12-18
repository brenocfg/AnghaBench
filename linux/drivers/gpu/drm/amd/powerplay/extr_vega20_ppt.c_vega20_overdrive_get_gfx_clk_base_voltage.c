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
typedef  int uint32_t ;
struct smu_context {int dummy; } ;

/* Variables and functions */
 int AVFS_CURVE ; 
 int OD8_HOTCURVE_TEMPERATURE ; 
 int /*<<< orphan*/  SMU_MSG_GetAVFSVoltageByDpm ; 
 int VOLTAGE_SCALE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  smu_read_smc_arg (struct smu_context*,int*) ; 
 int smu_send_smc_msg_with_param (struct smu_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vega20_overdrive_get_gfx_clk_base_voltage(struct smu_context *smu,
						     uint32_t *voltage,
						     uint32_t freq)
{
	int ret;

	ret = smu_send_smc_msg_with_param(smu,
			SMU_MSG_GetAVFSVoltageByDpm,
			((AVFS_CURVE << 24) | (OD8_HOTCURVE_TEMPERATURE << 16) | freq));
	if (ret) {
		pr_err("[GetBaseVoltage] failed to get GFXCLK AVFS voltage from SMU!");
		return ret;
	}

	smu_read_smc_arg(smu, voltage);
	*voltage = *voltage / VOLTAGE_SCALE;

	return 0;
}