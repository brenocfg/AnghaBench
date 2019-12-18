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
typedef  int /*<<< orphan*/  u8 ;
struct st_lsm6dsx_sensor {size_t id; int /*<<< orphan*/  odr; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_reg {int /*<<< orphan*/  mask; scalar_t__ addr; } ;
struct st_lsm6dsx_hw {scalar_t__ enable_mask; TYPE_1__* settings; } ;
struct TYPE_2__ {struct st_lsm6dsx_reg* batch; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_ODR_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_MAX_FIFO_ODR_VAL ; 
 scalar_t__ ST_LSM6DSX_REG_FIFO_MODE_ADDR ; 
 int ST_LSM6DSX_SHIFT_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_check_odr (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_update_bits_locked (struct st_lsm6dsx_hw*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_lsm6dsx_set_fifo_odr(struct st_lsm6dsx_sensor *sensor,
				   bool enable)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	const struct st_lsm6dsx_reg *batch_reg;
	u8 data;

	batch_reg = &hw->settings->batch[sensor->id];
	if (batch_reg->addr) {
		int val;

		if (enable) {
			int err;

			err = st_lsm6dsx_check_odr(sensor, sensor->odr,
						   &data);
			if (err < 0)
				return err;
		} else {
			data = 0;
		}
		val = ST_LSM6DSX_SHIFT_VAL(data, batch_reg->mask);
		return st_lsm6dsx_update_bits_locked(hw, batch_reg->addr,
						     batch_reg->mask, val);
	} else {
		data = hw->enable_mask ? ST_LSM6DSX_MAX_FIFO_ODR_VAL : 0;
		return st_lsm6dsx_update_bits_locked(hw,
					ST_LSM6DSX_REG_FIFO_MODE_ADDR,
					ST_LSM6DSX_FIFO_ODR_MASK,
					FIELD_PREP(ST_LSM6DSX_FIFO_ODR_MASK,
						   data));
	}
}