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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {size_t count; scalar_t__* leakage_id; scalar_t__* actual_voltage; } ;
struct TYPE_3__ {size_t count; scalar_t__* leakage_id; scalar_t__* actual_voltage; } ;
struct smu7_hwmgr {TYPE_2__ vddci_leakage; TYPE_1__ vddc_leakage; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 scalar_t__ ATOM_VIRTUAL_VOLTAGE_ID0 ; 
 int SMU7_MAX_LEAKAGE_COUNT ; 
 scalar_t__ atomctrl_get_leakage_id_from_efuse (struct pp_hwmgr*,scalar_t__*) ; 
 scalar_t__ atomctrl_get_leakage_vddc_base_on_leakage (struct pp_hwmgr*,scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int smu7_get_elb_voltages(struct pp_hwmgr *hwmgr)
{
	uint16_t virtual_voltage_id, vddc, vddci, efuse_voltage_id;
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);
	int i;

	if (atomctrl_get_leakage_id_from_efuse(hwmgr, &efuse_voltage_id) == 0) {
		for (i = 0; i < SMU7_MAX_LEAKAGE_COUNT; i++) {
			virtual_voltage_id = ATOM_VIRTUAL_VOLTAGE_ID0 + i;
			if (atomctrl_get_leakage_vddc_base_on_leakage(hwmgr, &vddc, &vddci,
								virtual_voltage_id,
								efuse_voltage_id) == 0) {
				if (vddc != 0 && vddc != virtual_voltage_id) {
					data->vddc_leakage.actual_voltage[data->vddc_leakage.count] = vddc;
					data->vddc_leakage.leakage_id[data->vddc_leakage.count] = virtual_voltage_id;
					data->vddc_leakage.count++;
				}
				if (vddci != 0 && vddci != virtual_voltage_id) {
					data->vddci_leakage.actual_voltage[data->vddci_leakage.count] = vddci;
					data->vddci_leakage.leakage_id[data->vddci_leakage.count] = virtual_voltage_id;
					data->vddci_leakage.count++;
				}
			}
		}
	}
	return 0;
}