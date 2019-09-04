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
struct fimc_is {size_t config_index; unsigned int sensor_index; struct chain_config* config; } ;
struct chain_config {unsigned int* p_region_index; } ;

/* Variables and functions */
 unsigned int HIC_SET_PARAMETER ; 
 int /*<<< orphan*/  MCUCTL_REG_ISSR (int) ; 
 unsigned int __get_pending_param_count (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_hw_set_intgr0_gd0 (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_hw_wait_intmsr0_intmsd0 (struct fimc_is*) ; 
 int /*<<< orphan*/  mcuctl_write (unsigned int,struct fimc_is*,int /*<<< orphan*/ ) ; 

int fimc_is_hw_set_param(struct fimc_is *is)
{
	struct chain_config *config = &is->config[is->config_index];
	unsigned int param_count = __get_pending_param_count(is);

	fimc_is_hw_wait_intmsr0_intmsd0(is);

	mcuctl_write(HIC_SET_PARAMETER, is, MCUCTL_REG_ISSR(0));
	mcuctl_write(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_write(is->config_index, is, MCUCTL_REG_ISSR(2));

	mcuctl_write(param_count, is, MCUCTL_REG_ISSR(3));
	mcuctl_write(config->p_region_index[0], is, MCUCTL_REG_ISSR(4));
	mcuctl_write(config->p_region_index[1], is, MCUCTL_REG_ISSR(5));

	fimc_is_hw_set_intgr0_gd0(is);
	return 0;
}