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
typedef  int u8 ;
struct st_lsm6dsx_sensor {scalar_t__ ts_ref; } ;
struct st_lsm6dsx_hw {int enable_mask; struct iio_dev** iio_devs; } ;
struct iio_dev {int dummy; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int BIT (size_t) ; 
 int EINVAL ; 
#define  ST_LSM6DSX_ACC_TAG 132 
#define  ST_LSM6DSX_EXT0_TAG 131 
#define  ST_LSM6DSX_EXT1_TAG 130 
#define  ST_LSM6DSX_EXT2_TAG 129 
#define  ST_LSM6DSX_GYRO_TAG 128 
 size_t ST_LSM6DSX_ID_ACC ; 
 size_t ST_LSM6DSX_ID_EXT0 ; 
 size_t ST_LSM6DSX_ID_EXT1 ; 
 size_t ST_LSM6DSX_ID_EXT2 ; 
 size_t ST_LSM6DSX_ID_GYRO ; 
 struct st_lsm6dsx_sensor* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int*,scalar_t__) ; 

__attribute__((used)) static int
st_lsm6dsx_push_tagged_data(struct st_lsm6dsx_hw *hw, u8 tag,
			    u8 *data, s64 ts)
{
	struct st_lsm6dsx_sensor *sensor;
	struct iio_dev *iio_dev;

	/*
	 * EXT_TAG are managed in FIFO fashion so ST_LSM6DSX_EXT0_TAG
	 * corresponds to the first enabled channel, ST_LSM6DSX_EXT1_TAG
	 * to the second one and ST_LSM6DSX_EXT2_TAG to the last enabled
	 * channel
	 */
	switch (tag) {
	case ST_LSM6DSX_GYRO_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_GYRO];
		break;
	case ST_LSM6DSX_ACC_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_ACC];
		break;
	case ST_LSM6DSX_EXT0_TAG:
		if (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT0))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT0];
		else if (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT1))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT1];
		else
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		break;
	case ST_LSM6DSX_EXT1_TAG:
		if ((hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT0)) &&
		    (hw->enable_mask & BIT(ST_LSM6DSX_ID_EXT1)))
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT1];
		else
			iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		break;
	case ST_LSM6DSX_EXT2_TAG:
		iio_dev = hw->iio_devs[ST_LSM6DSX_ID_EXT2];
		break;
	default:
		return -EINVAL;
	}

	sensor = iio_priv(iio_dev);
	iio_push_to_buffers_with_timestamp(iio_dev, data,
					   ts + sensor->ts_ref);

	return 0;
}