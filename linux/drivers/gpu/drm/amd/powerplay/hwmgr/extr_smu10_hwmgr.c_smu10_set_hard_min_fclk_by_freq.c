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
typedef  scalar_t__ uint32_t ;
struct smu10_hwmgr {scalar_t__ f_actual_hard_min_freq; } ;
struct pp_hwmgr {scalar_t__ backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPSMC_MSG_SetHardMinFclkByFreq ; 
 int /*<<< orphan*/  smum_send_msg_to_smc_with_parameter (struct pp_hwmgr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smu10_set_hard_min_fclk_by_freq(struct pp_hwmgr *hwmgr, uint32_t clock)
{
	struct smu10_hwmgr *smu10_data = (struct smu10_hwmgr *)(hwmgr->backend);

	if (smu10_data->f_actual_hard_min_freq &&
		smu10_data->f_actual_hard_min_freq != clock) {
		smu10_data->f_actual_hard_min_freq = clock;
		smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetHardMinFclkByFreq,
					smu10_data->f_actual_hard_min_freq);
	}
	return 0;
}