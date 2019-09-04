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
struct ad5758_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_CAL_MEM_UNREFRESHED_MSK ; 
 int /*<<< orphan*/  AD5758_DAC_CONFIG ; 
 unsigned int AD5758_DAC_CONFIG_SR_CLOCK_MODE (unsigned int) ; 
 unsigned long AD5758_DAC_CONFIG_SR_CLOCK_MSK ; 
 unsigned int AD5758_DAC_CONFIG_SR_EN_MODE (int) ; 
 unsigned long AD5758_DAC_CONFIG_SR_EN_MSK ; 
 unsigned int AD5758_DAC_CONFIG_SR_STEP_MODE (unsigned int) ; 
 unsigned long AD5758_DAC_CONFIG_SR_STEP_MSK ; 
 int /*<<< orphan*/  AD5758_DIGITAL_DIAG_RESULTS ; 
 int ad5758_spi_write_mask (struct ad5758_state*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 int ad5758_wait_for_task_complete (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5758_slew_rate_set(struct ad5758_state *st,
				unsigned int sr_clk_idx,
				unsigned int sr_step_idx)
{
	unsigned int mode;
	unsigned long int mask;
	int ret;

	mask = AD5758_DAC_CONFIG_SR_EN_MSK |
	       AD5758_DAC_CONFIG_SR_CLOCK_MSK |
	       AD5758_DAC_CONFIG_SR_STEP_MSK;
	mode = AD5758_DAC_CONFIG_SR_EN_MODE(1) |
	       AD5758_DAC_CONFIG_SR_STEP_MODE(sr_step_idx) |
	       AD5758_DAC_CONFIG_SR_CLOCK_MODE(sr_clk_idx);

	ret = ad5758_spi_write_mask(st, AD5758_DAC_CONFIG, mask, mode);
	if (ret < 0)
		return ret;

	/* Wait to allow time for the internal calibrations to complete */
	return ad5758_wait_for_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
}