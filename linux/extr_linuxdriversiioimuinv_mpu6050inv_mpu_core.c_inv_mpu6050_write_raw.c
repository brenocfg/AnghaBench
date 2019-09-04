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
struct inv_mpu6050_state {int /*<<< orphan*/  lock; TYPE_1__* reg; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  accl_offset; int /*<<< orphan*/  gyro_offset; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_ACCEL 131 
#define  IIO_ANGL_VEL 130 
#define  IIO_CHAN_INFO_CALIBBIAS 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int inv_mpu6050_sensor_set (struct inv_mpu6050_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int inv_mpu6050_set_power_itg (struct inv_mpu6050_state*,int) ; 
 int inv_mpu6050_write_accel_scale (struct inv_mpu6050_state*,int) ; 
 int inv_mpu6050_write_gyro_scale (struct inv_mpu6050_state*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int inv_mpu6050_write_raw(struct iio_dev *indio_dev,
				 struct iio_chan_spec const *chan,
				 int val, int val2, long mask)
{
	struct inv_mpu6050_state  *st = iio_priv(indio_dev);
	int result;

	/*
	 * we should only update scale when the chip is disabled, i.e.
	 * not running
	 */
	result = iio_device_claim_direct_mode(indio_dev);
	if (result)
		return result;

	mutex_lock(&st->lock);
	result = inv_mpu6050_set_power_itg(st, true);
	if (result)
		goto error_write_raw_unlock;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			result = inv_mpu6050_write_gyro_scale(st, val2);
			break;
		case IIO_ACCEL:
			result = inv_mpu6050_write_accel_scale(st, val2);
			break;
		default:
			result = -EINVAL;
			break;
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			result = inv_mpu6050_sensor_set(st,
							st->reg->gyro_offset,
							chan->channel2, val);
			break;
		case IIO_ACCEL:
			result = inv_mpu6050_sensor_set(st,
							st->reg->accl_offset,
							chan->channel2, val);
			break;
		default:
			result = -EINVAL;
			break;
		}
		break;
	default:
		result = -EINVAL;
		break;
	}

	result |= inv_mpu6050_set_power_itg(st, false);
error_write_raw_unlock:
	mutex_unlock(&st->lock);
	iio_device_release_direct_mode(indio_dev);

	return result;
}