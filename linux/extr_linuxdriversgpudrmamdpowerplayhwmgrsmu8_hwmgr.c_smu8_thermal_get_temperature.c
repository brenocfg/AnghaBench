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
typedef  int uint32_t ;
struct pp_hwmgr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGS_IND_REG__SMC ; 
 int /*<<< orphan*/  CUR_TEMP ; 
 int /*<<< orphan*/  CUR_TEMP_RANGE_SEL ; 
 int PHM_GET_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PP_TEMPERATURE_UNITS_PER_CENTIGRADES ; 
 int /*<<< orphan*/  THM_TCON_CUR_TMP ; 
 int cgs_read_ind_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixTHM_TCON_CUR_TMP ; 

__attribute__((used)) static int smu8_thermal_get_temperature(struct pp_hwmgr *hwmgr)
{
	int actual_temp = 0;
	uint32_t val = cgs_read_ind_register(hwmgr->device,
					     CGS_IND_REG__SMC, ixTHM_TCON_CUR_TMP);
	uint32_t temp = PHM_GET_FIELD(val, THM_TCON_CUR_TMP, CUR_TEMP);

	if (PHM_GET_FIELD(val, THM_TCON_CUR_TMP, CUR_TEMP_RANGE_SEL))
		actual_temp = ((temp / 8) - 49) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	else
		actual_temp = (temp / 8) * PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	return actual_temp;
}