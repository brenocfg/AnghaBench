#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* nbp_memory_clock; } ;
struct smu8_hwmgr {TYPE_3__ sys_info; } ;
struct TYPE_4__ {struct phm_clock_voltage_dependency_table* vddc_dependency_on_sclk; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; TYPE_1__ dyn_state; struct smu8_hwmgr* backend; } ;
struct phm_clock_voltage_dependency_table {int count; TYPE_2__* entries; } ;
typedef  enum pp_clock_type { ____Placeholder_pp_clock_type } pp_clock_type ;
struct TYPE_5__ {int clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CURR_MCLK_INDEX ; 
 int /*<<< orphan*/  CURR_SCLK_INDEX ; 
 int PHM_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PP_MCLK 129 
#define  PP_SCLK 128 
 int SMU8_NUM_NBPMEMORYCLOCK ; 
 int /*<<< orphan*/  TARGET_AND_CURRENT_PROFILE_INDEX ; 
 int /*<<< orphan*/  cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixTARGET_AND_CURRENT_PROFILE_INDEX ; 
 int sprintf (char*,char*,int,int,char*) ; 

__attribute__((used)) static int smu8_print_clock_levels(struct pp_hwmgr *hwmgr,
		enum pp_clock_type type, char *buf)
{
	struct smu8_hwmgr *data = hwmgr->backend;
	struct phm_clock_voltage_dependency_table *sclk_table =
			hwmgr->dyn_state.vddc_dependency_on_sclk;
	int i, now, size = 0;

	switch (type) {
	case PP_SCLK:
		now = PHM_GET_FIELD(cgs_read_ind_register(hwmgr->device,
				CGS_IND_REG__SMC,
				ixTARGET_AND_CURRENT_PROFILE_INDEX),
				TARGET_AND_CURRENT_PROFILE_INDEX,
				CURR_SCLK_INDEX);

		for (i = 0; i < sclk_table->count; i++)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					i, sclk_table->entries[i].clk / 100,
					(i == now) ? "*" : "");
		break;
	case PP_MCLK:
		now = PHM_GET_FIELD(cgs_read_ind_register(hwmgr->device,
				CGS_IND_REG__SMC,
				ixTARGET_AND_CURRENT_PROFILE_INDEX),
				TARGET_AND_CURRENT_PROFILE_INDEX,
				CURR_MCLK_INDEX);

		for (i = SMU8_NUM_NBPMEMORYCLOCK; i > 0; i--)
			size += sprintf(buf + size, "%d: %uMhz %s\n",
					SMU8_NUM_NBPMEMORYCLOCK-i, data->sys_info.nbp_memory_clock[i-1] / 100,
					(SMU8_NUM_NBPMEMORYCLOCK-i == now) ? "*" : "");
		break;
	default:
		break;
	}
	return size;
}