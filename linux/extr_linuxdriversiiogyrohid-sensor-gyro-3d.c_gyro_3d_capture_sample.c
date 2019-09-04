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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct gyro_3d_state {int /*<<< orphan*/ * gyro_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_SCAN_INDEX_X ; 
 int EINVAL ; 
#define  HID_USAGE_SENSOR_ANGL_VELOCITY_X_AXIS 130 
#define  HID_USAGE_SENSOR_ANGL_VELOCITY_Y_AXIS 129 
#define  HID_USAGE_SENSOR_ANGL_VELOCITY_Z_AXIS 128 
 struct gyro_3d_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int gyro_3d_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct gyro_3d_state *gyro_state = iio_priv(indio_dev);
	int offset;
	int ret = -EINVAL;

	switch (usage_id) {
	case HID_USAGE_SENSOR_ANGL_VELOCITY_X_AXIS:
	case HID_USAGE_SENSOR_ANGL_VELOCITY_Y_AXIS:
	case HID_USAGE_SENSOR_ANGL_VELOCITY_Z_AXIS:
		offset = usage_id - HID_USAGE_SENSOR_ANGL_VELOCITY_X_AXIS;
		gyro_state->gyro_val[CHANNEL_SCAN_INDEX_X + offset] =
						*(u32 *)raw_data;
		ret = 0;
	break;
	default:
		break;
	}

	return ret;
}