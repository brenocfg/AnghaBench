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
typedef  int /*<<< orphan*/  uint8_t ;
struct bios_parser {int dummy; } ;
struct atom_get_smu_clock_info_parameters_v3_1 {int /*<<< orphan*/  syspll_id; int /*<<< orphan*/  command; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {unsigned int syspllvcofreq_10khz; } ;
struct atom_get_smu_clock_info_output_parameters_v3_1 {TYPE_1__ atom_smu_outputclkfreq; } ;

/* Variables and functions */
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,struct atom_get_smu_clock_info_parameters_v3_1) ; 
 int /*<<< orphan*/  GET_SMU_CLOCK_INFO_V3_1_GET_PLLVCO_FREQ ; 
 int /*<<< orphan*/  getsmuclockinfo ; 
 int /*<<< orphan*/  memmove (struct atom_get_smu_clock_info_output_parameters_v3_1*,struct atom_get_smu_clock_info_parameters_v3_1*,int) ; 

__attribute__((used)) static unsigned int get_smu_clock_info_v3_1(struct bios_parser *bp, uint8_t id)
{
	struct atom_get_smu_clock_info_parameters_v3_1 smu_input = {0};
	struct atom_get_smu_clock_info_output_parameters_v3_1 smu_output;

	smu_input.command = GET_SMU_CLOCK_INFO_V3_1_GET_PLLVCO_FREQ;
	smu_input.syspll_id = id;

	/* Get Specific Clock */
	if (EXEC_BIOS_CMD_TABLE(getsmuclockinfo, smu_input)) {
		memmove(&smu_output, &smu_input, sizeof(
			struct atom_get_smu_clock_info_parameters_v3_1));
		return smu_output.atom_smu_outputclkfreq.syspllvcofreq_10khz;
	}

	return 0;
}