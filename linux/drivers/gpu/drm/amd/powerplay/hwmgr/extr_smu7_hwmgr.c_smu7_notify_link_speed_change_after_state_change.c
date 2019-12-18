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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct smu7_power_state {int dummy; } ;
struct smu7_hwmgr {scalar_t__ pspp_notify_required; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;
struct phm_set_power_state_input {int /*<<< orphan*/  pnew_state; } ;

/* Variables and functions */
 scalar_t__ PCIE_PERF_REQ_GEN1 ; 
 scalar_t__ PCIE_PERF_REQ_GEN2 ; 
 scalar_t__ PCIE_PERF_REQ_GEN3 ; 
 scalar_t__ PP_PCIEGen2 ; 
 scalar_t__ PP_PCIEGen3 ; 
 scalar_t__ amdgpu_acpi_pcie_performance_request (int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct smu7_power_state* cast_const_phw_smu7_power_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ smu7_get_current_pcie_speed (struct pp_hwmgr*) ; 
 scalar_t__ smu7_get_maximum_link_speed (struct pp_hwmgr*,struct smu7_power_state const*) ; 

__attribute__((used)) static int smu7_notify_link_speed_change_after_state_change(
		struct pp_hwmgr *hwmgr, const void *input)
{
	const struct phm_set_power_state_input *states =
			(const struct phm_set_power_state_input *)input;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	const struct smu7_power_state *smu7_ps =
			cast_const_phw_smu7_power_state(states->pnew_state);
	uint16_t target_link_speed = smu7_get_maximum_link_speed(hwmgr, smu7_ps);
	uint8_t  request;

	if (data->pspp_notify_required) {
		if (target_link_speed == PP_PCIEGen3)
			request = PCIE_PERF_REQ_GEN3;
		else if (target_link_speed == PP_PCIEGen2)
			request = PCIE_PERF_REQ_GEN2;
		else
			request = PCIE_PERF_REQ_GEN1;

		if (request == PCIE_PERF_REQ_GEN1 &&
				smu7_get_current_pcie_speed(hwmgr) > 0)
			return 0;

#ifdef CONFIG_ACPI
		if (amdgpu_acpi_pcie_performance_request(hwmgr->adev, request, false)) {
			if (PP_PCIEGen2 == target_link_speed)
				pr_info("PSPP request to switch to Gen2 from Gen3 Failed!");
			else
				pr_info("PSPP request to switch to Gen1 from Gen2 Failed!");
		}
#endif
	}

	return 0;
}