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
typedef  int uint16_t ;
struct smu7_power_state {int dummy; } ;
struct smu7_hwmgr {scalar_t__ force_pcie_gen; int pspp_notify_required; } ;
struct pp_hwmgr {int /*<<< orphan*/  adev; scalar_t__ backend; } ;
struct phm_set_power_state_input {int /*<<< orphan*/  pcurrent_state; int /*<<< orphan*/  pnew_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_PERF_REQ_GEN2 ; 
 int /*<<< orphan*/  PCIE_PERF_REQ_GEN3 ; 
#define  PP_PCIEGen2 129 
#define  PP_PCIEGen3 128 
 scalar_t__ PP_PCIEGenInvalid ; 
 int /*<<< orphan*/  amdgpu_acpi_pcie_performance_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct smu7_power_state* cast_const_phw_smu7_power_state (int /*<<< orphan*/ ) ; 
 int smu7_get_current_pcie_speed (struct pp_hwmgr*) ; 
 int smu7_get_maximum_link_speed (struct pp_hwmgr*,struct smu7_power_state const*) ; 

__attribute__((used)) static int smu7_request_link_speed_change_before_state_change(
		struct pp_hwmgr *hwmgr, const void *input)
{
	const struct phm_set_power_state_input *states =
			(const struct phm_set_power_state_input *)input;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	const struct smu7_power_state *smu7_nps =
			cast_const_phw_smu7_power_state(states->pnew_state);
	const struct smu7_power_state *polaris10_cps =
			cast_const_phw_smu7_power_state(states->pcurrent_state);

	uint16_t target_link_speed = smu7_get_maximum_link_speed(hwmgr, smu7_nps);
	uint16_t current_link_speed;

	if (data->force_pcie_gen == PP_PCIEGenInvalid)
		current_link_speed = smu7_get_maximum_link_speed(hwmgr, polaris10_cps);
	else
		current_link_speed = data->force_pcie_gen;

	data->force_pcie_gen = PP_PCIEGenInvalid;
	data->pspp_notify_required = false;

	if (target_link_speed > current_link_speed) {
		switch (target_link_speed) {
#ifdef CONFIG_ACPI
		case PP_PCIEGen3:
			if (0 == amdgpu_acpi_pcie_performance_request(hwmgr->adev, PCIE_PERF_REQ_GEN3, false))
				break;
			data->force_pcie_gen = PP_PCIEGen2;
			if (current_link_speed == PP_PCIEGen2)
				break;
			/* fall through */
		case PP_PCIEGen2:
			if (0 == amdgpu_acpi_pcie_performance_request(hwmgr->adev, PCIE_PERF_REQ_GEN2, false))
				break;
#endif
			/* fall through */
		default:
			data->force_pcie_gen = smu7_get_current_pcie_speed(hwmgr);
			break;
		}
	} else {
		if (target_link_speed < current_link_speed)
			data->pspp_notify_required = true;
	}

	return 0;
}