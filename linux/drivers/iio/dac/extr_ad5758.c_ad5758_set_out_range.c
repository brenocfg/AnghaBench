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
 int /*<<< orphan*/  AD5758_DAC_CONFIG_RANGE_MODE (int) ; 
 int /*<<< orphan*/  AD5758_DAC_CONFIG_RANGE_MSK ; 
 int /*<<< orphan*/  AD5758_DIGITAL_DIAG_RESULTS ; 
 int ad5758_spi_write_mask (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ad5758_wait_for_task_complete (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5758_set_out_range(struct ad5758_state *st, int range)
{
	int ret;

	ret = ad5758_spi_write_mask(st, AD5758_DAC_CONFIG,
				    AD5758_DAC_CONFIG_RANGE_MSK,
				    AD5758_DAC_CONFIG_RANGE_MODE(range));
	if (ret < 0)
		return ret;

	/* Wait to allow time for the internal calibrations to complete */
	return ad5758_wait_for_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
}