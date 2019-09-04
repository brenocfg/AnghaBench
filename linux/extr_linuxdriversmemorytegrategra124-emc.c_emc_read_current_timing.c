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
struct tegra_emc {scalar_t__ regs; } ;
struct emc_timing {scalar_t__ emc_mode_reset; scalar_t__ emc_mode_4; scalar_t__ emc_mode_2; scalar_t__ emc_mode_1; scalar_t__ emc_zcal_cnt_long; scalar_t__ emc_auto_cal_interval; void* emc_cfg; void** emc_burst_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ EMC_CFG ; 
 scalar_t__* emc_burst_regs ; 
 void* readl (scalar_t__) ; 

__attribute__((used)) static void emc_read_current_timing(struct tegra_emc *emc,
				    struct emc_timing *timing)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(emc_burst_regs); ++i)
		timing->emc_burst_data[i] =
			readl(emc->regs + emc_burst_regs[i]);

	timing->emc_cfg = readl(emc->regs + EMC_CFG);

	timing->emc_auto_cal_interval = 0;
	timing->emc_zcal_cnt_long = 0;
	timing->emc_mode_1 = 0;
	timing->emc_mode_2 = 0;
	timing->emc_mode_4 = 0;
	timing->emc_mode_reset = 0;
}