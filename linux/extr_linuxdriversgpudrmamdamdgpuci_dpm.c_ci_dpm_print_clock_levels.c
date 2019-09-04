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
typedef  int uint32_t ;
struct ci_single_dpm_table {int count; TYPE_2__* dpm_levels; } ;
struct TYPE_3__ {struct ci_single_dpm_table pcie_speed_table; struct ci_single_dpm_table mclk_table; struct ci_single_dpm_table sclk_table; } ;
struct ci_power_info {TYPE_1__ dpm_table; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;
struct TYPE_4__ {int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_API_GetMclkFrequency ; 
 int /*<<< orphan*/  PPSMC_MSG_API_GetSclkFrequency ; 
#define  PP_MCLK 130 
#define  PP_PCIE 129 
#define  PP_SCLK 128 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ci_send_msg_to_smc (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int ci_get_current_pcie_speed (struct amdgpu_device*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmSMC_MSG_ARG_0 ; 
 int sprintf (char*,char*,int,...) ; 

__attribute__((used)) static int ci_dpm_print_clock_levels(void *handle,
		enum pp_clock_type type, char *buf)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	struct ci_power_info *pi = ci_get_pi(adev);
	struct ci_single_dpm_table *sclk_table = &pi->dpm_table.sclk_table;
	struct ci_single_dpm_table *mclk_table = &pi->dpm_table.mclk_table;
	struct ci_single_dpm_table *pcie_table = &pi->dpm_table.pcie_speed_table;

	int i, now, size = 0;
	uint32_t clock, pcie_speed;

	switch (type) {
	case PP_SCLK:
		amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_API_GetSclkFrequency);
		clock = RREG32(mmSMC_MSG_ARG_0);

		for (i = 0; i < sclk_table->count; i++) {
			if (clock > sclk_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < sclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_MCLK:
		amdgpu_ci_send_msg_to_smc(adev, PPSMC_MSG_API_GetMclkFrequency);
		clock = RREG32(mmSMC_MSG_ARG_0);

		for (i = 0; i < mclk_table->count; i++) {
			if (clock > mclk_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < mclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, mclk_table->dpm_levels[i].value / 100,
					(i == now) ? "*" : "");
		break;
	case PP_PCIE:
		pcie_speed = ci_get_current_pcie_speed(adev);
		for (i = 0; i < pcie_table->count; i++) {
			if (pcie_speed != pcie_table->dpm_levels[i].value)
				continue;
			break;
		}
		now = i;

		for (i = 0; i < pcie_table->count; i++)
			size += sprintf(buf + size, "%d: %s %s\n", i,
					(pcie_table->dpm_levels[i].value == 0) ? "2.5GT/s, x1" :
					(pcie_table->dpm_levels[i].value == 1) ? "5.0GT/s, x16" :
					(pcie_table->dpm_levels[i].value == 2) ? "8.0GT/s, x16" : "",
					(i == now) ? "*" : "");
		break;
	default:
		break;
	}

	return size;
}