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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int LedPin0; int LedPin1; int LedPin2; } ;
struct TYPE_3__ {TYPE_2__ pp_table; } ;
struct vega10_hwmgr {TYPE_1__ smc_state_table; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct pp_atomfwctrl_voltage_table {int mask_low; } ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_2__ PPTable_t ;

/* Variables and functions */
 int /*<<< orphan*/  VOLTAGE_OBJ_GPIO_LUT ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_LEDDPM ; 
 scalar_t__ pp_atomfwctrl_get_voltage_table_v4 (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pp_atomfwctrl_voltage_table*) ; 

__attribute__((used)) static int vega10_setup_dpm_led_config(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);

	struct pp_atomfwctrl_voltage_table table;
	uint8_t i, j;
	uint32_t mask = 0;
	uint32_t tmp;
	int32_t ret = 0;

	ret = pp_atomfwctrl_get_voltage_table_v4(hwmgr, VOLTAGE_TYPE_LEDDPM,
						VOLTAGE_OBJ_GPIO_LUT, &table);

	if (!ret) {
		tmp = table.mask_low;
		for (i = 0, j = 0; i < 32; i++) {
			if (tmp & 1) {
				mask |= (uint32_t)(i << (8 * j));
				if (++j >= 3)
					break;
			}
			tmp >>= 1;
		}
	}

	pp_table->LedPin0 = (uint8_t)(mask & 0xff);
	pp_table->LedPin1 = (uint8_t)((mask >> 8) & 0xff);
	pp_table->LedPin2 = (uint8_t)((mask >> 16) & 0xff);
	return 0;
}