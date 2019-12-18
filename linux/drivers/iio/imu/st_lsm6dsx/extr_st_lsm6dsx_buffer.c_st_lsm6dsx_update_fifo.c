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
struct st_lsm6dsx_sensor {scalar_t__ id; int /*<<< orphan*/  watermark; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {scalar_t__ fifo_mode; int /*<<< orphan*/  conf_lock; scalar_t__ enable_mask; } ;

/* Variables and functions */
 scalar_t__ ST_LSM6DSX_FIFO_BYPASS ; 
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_CONT ; 
 scalar_t__ ST_LSM6DSX_ID_EXT0 ; 
 scalar_t__ ST_LSM6DSX_ID_EXT1 ; 
 scalar_t__ ST_LSM6DSX_ID_EXT2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_flush_fifo (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_reset_hw_ts (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_sensor_set_enable (struct st_lsm6dsx_sensor*,int) ; 
 int st_lsm6dsx_set_fifo_mode (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_set_fifo_odr (struct st_lsm6dsx_sensor*,int) ; 
 int st_lsm6dsx_shub_set_enable (struct st_lsm6dsx_sensor*,int) ; 
 int st_lsm6dsx_update_decimators (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_update_watermark (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ) ; 

int st_lsm6dsx_update_fifo(struct st_lsm6dsx_sensor *sensor, bool enable)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	int err;

	mutex_lock(&hw->conf_lock);

	if (hw->fifo_mode != ST_LSM6DSX_FIFO_BYPASS) {
		err = st_lsm6dsx_flush_fifo(hw);
		if (err < 0)
			goto out;
	}

	if (sensor->id == ST_LSM6DSX_ID_EXT0 ||
	    sensor->id == ST_LSM6DSX_ID_EXT1 ||
	    sensor->id == ST_LSM6DSX_ID_EXT2) {
		err = st_lsm6dsx_shub_set_enable(sensor, enable);
		if (err < 0)
			goto out;
	} else {
		err = st_lsm6dsx_sensor_set_enable(sensor, enable);
		if (err < 0)
			goto out;

		err = st_lsm6dsx_set_fifo_odr(sensor, enable);
		if (err < 0)
			goto out;
	}

	err = st_lsm6dsx_update_decimators(hw);
	if (err < 0)
		goto out;

	err = st_lsm6dsx_update_watermark(sensor, sensor->watermark);
	if (err < 0)
		goto out;

	if (hw->enable_mask) {
		/* reset hw ts counter */
		err = st_lsm6dsx_reset_hw_ts(hw);
		if (err < 0)
			goto out;

		err = st_lsm6dsx_set_fifo_mode(hw, ST_LSM6DSX_FIFO_CONT);
	}

out:
	mutex_unlock(&hw->conf_lock);

	return err;
}