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
struct TYPE_3__ {size_t fsr; size_t accl_fs; } ;
struct inv_mpu6050_state {int /*<<< orphan*/  lock; TYPE_2__* reg; int /*<<< orphan*/  chip_type; TYPE_1__ chip_config; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  accl_offset; int /*<<< orphan*/  gyro_offset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 134 
#define  IIO_ANGL_VEL 133 
#define  IIO_CHAN_INFO_CALIBBIAS 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SCALE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  INV_ICM20602 ; 
 int INV_ICM20602_TEMP_OFFSET ; 
 int INV_ICM20602_TEMP_SCALE ; 
 int INV_MPU6050_TEMP_OFFSET ; 
 int INV_MPU6050_TEMP_SCALE ; 
 int* accel_scale ; 
 int* gyro_scale_6050 ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int inv_mpu6050_read_channel_data (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int inv_mpu6050_sensor_show (struct inv_mpu6050_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
inv_mpu6050_read_raw(struct iio_dev *indio_dev,
		     struct iio_chan_spec const *chan,
		     int *val, int *val2, long mask)
{
	struct inv_mpu6050_state  *st = iio_priv(indio_dev);
	int ret = 0;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		mutex_lock(&st->lock);
		ret = inv_mpu6050_read_channel_data(indio_dev, chan, val);
		mutex_unlock(&st->lock);
		iio_device_release_direct_mode(indio_dev);
		return ret;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			mutex_lock(&st->lock);
			*val  = 0;
			*val2 = gyro_scale_6050[st->chip_config.fsr];
			mutex_unlock(&st->lock);

			return IIO_VAL_INT_PLUS_NANO;
		case IIO_ACCEL:
			mutex_lock(&st->lock);
			*val = 0;
			*val2 = accel_scale[st->chip_config.accl_fs];
			mutex_unlock(&st->lock);

			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = 0;
			if (st->chip_type == INV_ICM20602)
				*val2 = INV_ICM20602_TEMP_SCALE;
			else
				*val2 = INV_MPU6050_TEMP_SCALE;

			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_OFFSET:
		switch (chan->type) {
		case IIO_TEMP:
			if (st->chip_type == INV_ICM20602)
				*val = INV_ICM20602_TEMP_OFFSET;
			else
				*val = INV_MPU6050_TEMP_OFFSET;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_CALIBBIAS:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			mutex_lock(&st->lock);
			ret = inv_mpu6050_sensor_show(st, st->reg->gyro_offset,
						chan->channel2, val);
			mutex_unlock(&st->lock);
			return IIO_VAL_INT;
		case IIO_ACCEL:
			mutex_lock(&st->lock);
			ret = inv_mpu6050_sensor_show(st, st->reg->accl_offset,
						chan->channel2, val);
			mutex_unlock(&st->lock);
			return IIO_VAL_INT;

		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}