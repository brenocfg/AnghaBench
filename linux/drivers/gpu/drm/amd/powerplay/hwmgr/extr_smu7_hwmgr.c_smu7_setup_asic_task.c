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

/* Variables and functions */
 int /*<<< orphan*/  PP_ASSERT_WITH_CODE (int,char*,int) ; 
 int /*<<< orphan*/  smu7_check_mc_firmware (struct pp_hwmgr*) ; 
 int smu7_enable_acpi_power_management (struct pp_hwmgr*) ; 
 int smu7_get_mc_microcode_version (struct pp_hwmgr*) ; 
 int smu7_get_memory_type (struct pp_hwmgr*) ; 
 int smu7_init_power_gate_state (struct pp_hwmgr*) ; 
 int smu7_init_sclk_threshold (struct pp_hwmgr*) ; 
 int smu7_read_clock_registers (struct pp_hwmgr*) ; 

__attribute__((used)) static int smu7_setup_asic_task(struct pp_hwmgr *hwmgr)
{
	int tmp_result, result = 0;

	smu7_check_mc_firmware(hwmgr);

	tmp_result = smu7_read_clock_registers(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to read clock registers!", result = tmp_result);

	tmp_result = smu7_get_memory_type(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to get memory type!", result = tmp_result);

	tmp_result = smu7_enable_acpi_power_management(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to enable ACPI power management!", result = tmp_result);

	tmp_result = smu7_init_power_gate_state(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to init power gate state!", result = tmp_result);

	tmp_result = smu7_get_mc_microcode_version(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to get MC microcode version!", result = tmp_result);

	tmp_result = smu7_init_sclk_threshold(hwmgr);
	PP_ASSERT_WITH_CODE((0 == tmp_result),
			"Failed to init sclk threshold!", result = tmp_result);

	return result;
}