#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ad5758_state {TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5758_CAL_MEM_UNREFRESHED_MSK ; 
 int /*<<< orphan*/  AD5758_DIGITAL_DIAG_RESULTS ; 
 int /*<<< orphan*/  AD5758_KEY ; 
 int /*<<< orphan*/  AD5758_KEY_CODE_CALIB_MEM_REFRESH ; 
 int ad5758_spi_reg_write (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ad5758_wait_for_task_complete (struct ad5758_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ad5758_calib_mem_refresh(struct ad5758_state *st)
{
	int ret;

	ret = ad5758_spi_reg_write(st, AD5758_KEY,
				   AD5758_KEY_CODE_CALIB_MEM_REFRESH);
	if (ret < 0) {
		dev_err(&st->spi->dev,
			"Failed to initiate a calibration memory refresh\n");
		return ret;
	}

	/* Wait to allow time for the internal calibrations to complete */
	return ad5758_wait_for_task_complete(st, AD5758_DIGITAL_DIAG_RESULTS,
					     AD5758_CAL_MEM_UNREFRESHED_MSK);
}