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
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
typedef  enum bmi160_sensor_type { ____Placeholder_bmi160_sensor_type } bmi160_sensor_type ;

/* Variables and functions */
 int BMI160_ACCEL ; 
 int BMI160_GYRO ; 
 int EINVAL ; 
#define  IIO_ACCEL 129 
#define  IIO_ANGL_VEL 128 

__attribute__((used)) static enum bmi160_sensor_type bmi160_to_sensor(enum iio_chan_type iio_type)
{
	switch (iio_type) {
	case IIO_ACCEL:
		return BMI160_ACCEL;
	case IIO_ANGL_VEL:
		return BMI160_GYRO;
	default:
		return -EINVAL;
	}
}