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
struct TYPE_5__ {scalar_t__ ac_dc_switch_gpio_support; scalar_t__ regulator_hot_gpio_support; } ;
struct TYPE_6__ {scalar_t__ AcDcPolarity; scalar_t__ AcDcGpio; scalar_t__ VR1HotPolarity; scalar_t__ VR1HotGpio; scalar_t__ VR0HotPolarity; scalar_t__ VR0HotGpio; } ;
struct TYPE_4__ {TYPE_3__ pp_table; } ;
struct vega10_hwmgr {TYPE_2__ registry_data; TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct pp_atomfwctrl_gpio_parameters {scalar_t__ ucAcDcPolarity; scalar_t__ ucAcDcGpio; scalar_t__ ucVR1HotPolarity; scalar_t__ ucVR1HotGpio; scalar_t__ ucVR0HotPolarity; scalar_t__ ucVR0HotGpio; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ PPTable_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHM_PlatformCaps_AutomaticDCTransition ; 
 int /*<<< orphan*/  PHM_PlatformCaps_RegulatorHot ; 
 scalar_t__ PP_CAP (int /*<<< orphan*/ ) ; 
 int pp_atomfwctrl_get_gpio_information (struct pp_hwmgr*,struct pp_atomfwctrl_gpio_parameters*) ; 

__attribute__((used)) static int vega10_populate_gpio_parameters(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	struct pp_atomfwctrl_gpio_parameters gpio_params = {0};
	int result;

	result = pp_atomfwctrl_get_gpio_information(hwmgr, &gpio_params);
	if (!result) {
		if (PP_CAP(PHM_PlatformCaps_RegulatorHot) &&
		    data->registry_data.regulator_hot_gpio_support) {
			pp_table->VR0HotGpio = gpio_params.ucVR0HotGpio;
			pp_table->VR0HotPolarity = gpio_params.ucVR0HotPolarity;
			pp_table->VR1HotGpio = gpio_params.ucVR1HotGpio;
			pp_table->VR1HotPolarity = gpio_params.ucVR1HotPolarity;
		} else {
			pp_table->VR0HotGpio = 0;
			pp_table->VR0HotPolarity = 0;
			pp_table->VR1HotGpio = 0;
			pp_table->VR1HotPolarity = 0;
		}

		if (PP_CAP(PHM_PlatformCaps_AutomaticDCTransition) &&
		    data->registry_data.ac_dc_switch_gpio_support) {
			pp_table->AcDcGpio = gpio_params.ucAcDcGpio;
			pp_table->AcDcPolarity = gpio_params.ucAcDcPolarity;
		} else {
			pp_table->AcDcGpio = 0;
			pp_table->AcDcPolarity = 0;
		}
	}

	return result;
}