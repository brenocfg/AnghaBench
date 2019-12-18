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
typedef  int /*<<< orphan*/  u8 ;
struct st_lsm6dsx_sensor {int dummy; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/ * iio_devs; } ;
typedef  enum st_lsm6dsx_sensor_id { ____Placeholder_st_lsm6dsx_sensor_id } st_lsm6dsx_sensor_id ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ST_LSM6DSX_ID_EXT0 ; 
 int ST_LSM6DSX_MAX_SLV_NUM ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * st_lsm6dsx_ext_dev_table ; 
 int /*<<< orphan*/  st_lsm6dsx_shub_alloc_iiodev (struct st_lsm6dsx_hw*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int st_lsm6dsx_shub_check_wai (struct st_lsm6dsx_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_shub_init_device (struct st_lsm6dsx_sensor*) ; 

int st_lsm6dsx_shub_probe(struct st_lsm6dsx_hw *hw, const char *name)
{
	enum st_lsm6dsx_sensor_id id = ST_LSM6DSX_ID_EXT0;
	struct st_lsm6dsx_sensor *sensor;
	int err, i, num_ext_dev = 0;
	u8 i2c_addr = 0;

	for (i = 0; i < ARRAY_SIZE(st_lsm6dsx_ext_dev_table); i++) {
		err = st_lsm6dsx_shub_check_wai(hw, &i2c_addr,
					&st_lsm6dsx_ext_dev_table[i]);
		if (err == -ENODEV)
			continue;
		else if (err < 0)
			return err;

		hw->iio_devs[id] = st_lsm6dsx_shub_alloc_iiodev(hw, id,
						&st_lsm6dsx_ext_dev_table[i],
						i2c_addr, name);
		if (!hw->iio_devs[id])
			return -ENOMEM;

		sensor = iio_priv(hw->iio_devs[id]);
		err = st_lsm6dsx_shub_init_device(sensor);
		if (err < 0)
			return err;

		if (++num_ext_dev >= ST_LSM6DSX_MAX_SLV_NUM)
			break;
		id++;
	}

	return 0;
}