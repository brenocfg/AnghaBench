#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pp_hwmgr {int dummy; } ;
struct TYPE_3__ {int mask_low; } ;
typedef  TYPE_1__ pp_atomctrl_voltage_table ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_LedConfig ; 
 int /*<<< orphan*/  VOLTAGE_OBJ_GPIO_LUT ; 
 int /*<<< orphan*/  VOLTAGE_TYPE_LEDDPM ; 
 int atomctrl_get_voltage_table_v3 (struct pp_hwmgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fiji_setup_dpm_led_config(struct pp_hwmgr *hwmgr)
{
	pp_atomctrl_voltage_table param_led_dpm;
	int result = 0;
	u32 mask = 0;

	result = atomctrl_get_voltage_table_v3(hwmgr,
					       VOLTAGE_TYPE_LEDDPM, VOLTAGE_OBJ_GPIO_LUT,
					       &param_led_dpm);
	if (result == 0) {
		int i, j;
		u32 tmp = param_led_dpm.mask_low;

		for (i = 0, j = 0; i < 32; i++) {
			if (tmp & 1) {
				mask |= (i << (8 * j));
				if (++j >= 3)
					break;
			}
			tmp >>= 1;
		}
	}
	if (mask)
		smum_send_msg_to_smc_with_parameter(hwmgr,
						    PPSMC_MSG_LedConfig,
						    mask);
	return 0;
}