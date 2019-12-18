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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct st_lsm6dsx_sensor {int id; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_reg {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct st_lsm6dsx_hw {TYPE_2__* settings; int /*<<< orphan*/ * iio_devs; } ;
struct TYPE_4__ {TYPE_1__* odr_table; } ;
struct TYPE_3__ {struct st_lsm6dsx_reg reg; } ;

/* Variables and functions */
#define  ST_LSM6DSX_ID_ACC 131 
#define  ST_LSM6DSX_ID_EXT0 130 
#define  ST_LSM6DSX_ID_EXT1 129 
#define  ST_LSM6DSX_ID_EXT2 128 
 int ST_LSM6DSX_ID_MAX ; 
 unsigned int ST_LSM6DSX_SHIFT_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_check_odr (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_lsm6dsx_check_odr_dependency (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int) ; 
 int st_lsm6dsx_update_bits_locked (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int st_lsm6dsx_set_odr(struct st_lsm6dsx_sensor *sensor, u16 req_odr)
{
	struct st_lsm6dsx_sensor *ref_sensor = sensor;
	struct st_lsm6dsx_hw *hw = sensor->hw;
	const struct st_lsm6dsx_reg *reg;
	unsigned int data;
	u8 val = 0;
	int err;

	switch (sensor->id) {
	case ST_LSM6DSX_ID_EXT0:
	case ST_LSM6DSX_ID_EXT1:
	case ST_LSM6DSX_ID_EXT2:
	case ST_LSM6DSX_ID_ACC: {
		u16 odr;
		int i;

		/*
		 * i2c embedded controller relies on the accelerometer sensor as
		 * bus read/write trigger so we need to enable accel device
		 * at odr = max(accel_odr, ext_odr) in order to properly
		 * communicate with i2c slave devices
		 */
		ref_sensor = iio_priv(hw->iio_devs[ST_LSM6DSX_ID_ACC]);
		for (i = ST_LSM6DSX_ID_ACC; i < ST_LSM6DSX_ID_MAX; i++) {
			if (!hw->iio_devs[i] || i == sensor->id)
				continue;

			odr = st_lsm6dsx_check_odr_dependency(hw, req_odr, i);
			if (odr != req_odr)
				/* device already configured */
				return 0;
		}
		break;
	}
	default:
		break;
	}

	if (req_odr > 0) {
		err = st_lsm6dsx_check_odr(ref_sensor, req_odr, &val);
		if (err < 0)
			return err;
	}

	reg = &hw->settings->odr_table[ref_sensor->id].reg;
	data = ST_LSM6DSX_SHIFT_VAL(val, reg->mask);
	return st_lsm6dsx_update_bits_locked(hw, reg->addr, reg->mask, data);
}