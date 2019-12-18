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
struct sensor_open_extended {int self_calibration_mode; int i2c_sclk; scalar_t__ fast_open_sensor; scalar_t__ mipi_speed; scalar_t__ mclk; scalar_t__ mipi_lane_num; scalar_t__ actuator_type; } ;
struct fimc_is_sensor {TYPE_2__* drvdata; int /*<<< orphan*/  i2c_bus; } ;
struct fimc_is {int /*<<< orphan*/  is_dma_p_region; int /*<<< orphan*/  sensor_index; TYPE_1__* is_p_region; } ;
struct TYPE_4__ {int /*<<< orphan*/  open_timeout; int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  shared; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIC_OPEN_SENSOR ; 
 int /*<<< orphan*/  IS_ST_OPEN_SENSOR ; 
 int /*<<< orphan*/  MCUCTL_REG_ISSR (int) ; 
 int /*<<< orphan*/  fimc_is_hw_set_intgr0_gd0 (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_hw_wait_intmsr0_intmsd0 (struct fimc_is*) ; 
 int /*<<< orphan*/  fimc_is_mem_barrier () ; 
 int fimc_is_wait_event (struct fimc_is*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcuctl_write (int /*<<< orphan*/ ,struct fimc_is*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fimc_is_hw_open_sensor(struct fimc_is *is,
				  struct fimc_is_sensor *sensor)
{
	struct sensor_open_extended *soe = (void *)&is->is_p_region->shared;

	fimc_is_hw_wait_intmsr0_intmsd0(is);

	soe->self_calibration_mode = 1;
	soe->actuator_type = 0;
	soe->mipi_lane_num = 0;
	soe->mclk = 0;
	soe->mipi_speed	= 0;
	soe->fast_open_sensor = 0;
	soe->i2c_sclk = 88000000;

	fimc_is_mem_barrier();

	/*
	 * Some user space use cases hang up here without this
	 * empirically chosen delay.
	 */
	udelay(100);

	mcuctl_write(HIC_OPEN_SENSOR, is, MCUCTL_REG_ISSR(0));
	mcuctl_write(is->sensor_index, is, MCUCTL_REG_ISSR(1));
	mcuctl_write(sensor->drvdata->id, is, MCUCTL_REG_ISSR(2));
	mcuctl_write(sensor->i2c_bus, is, MCUCTL_REG_ISSR(3));
	mcuctl_write(is->is_dma_p_region, is, MCUCTL_REG_ISSR(4));

	fimc_is_hw_set_intgr0_gd0(is);

	return fimc_is_wait_event(is, IS_ST_OPEN_SENSOR, 1,
				  sensor->drvdata->open_timeout);
}