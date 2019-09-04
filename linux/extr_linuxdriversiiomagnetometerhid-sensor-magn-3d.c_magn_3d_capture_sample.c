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
struct magn_3d_state {int /*<<< orphan*/ ** magn_val_addr; } ;
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int CHANNEL_SCAN_INDEX_NORTH_MAGN_TILT_COMP ; 
 int CHANNEL_SCAN_INDEX_X ; 
 int EINVAL ; 
#define  HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH 134 
#define  HID_USAGE_SENSOR_ORIENT_COMP_TRUE_NORTH 133 
#define  HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS 132 
#define  HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Y_AXIS 131 
#define  HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Z_AXIS 130 
#define  HID_USAGE_SENSOR_ORIENT_MAGN_NORTH 129 
#define  HID_USAGE_SENSOR_ORIENT_TRUE_NORTH 128 
 struct magn_3d_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int magn_3d_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct magn_3d_state *magn_state = iio_priv(indio_dev);
	int offset;
	int ret = 0;
	u32 *iio_val = NULL;

	switch (usage_id) {
	case HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS:
	case HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Y_AXIS:
	case HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_Z_AXIS:
		offset = (usage_id - HID_USAGE_SENSOR_ORIENT_MAGN_FLUX_X_AXIS)
				+ CHANNEL_SCAN_INDEX_X;
	break;
	case HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH:
	case HID_USAGE_SENSOR_ORIENT_COMP_TRUE_NORTH:
	case HID_USAGE_SENSOR_ORIENT_MAGN_NORTH:
	case HID_USAGE_SENSOR_ORIENT_TRUE_NORTH:
		offset = (usage_id - HID_USAGE_SENSOR_ORIENT_COMP_MAGN_NORTH)
				+ CHANNEL_SCAN_INDEX_NORTH_MAGN_TILT_COMP;
	break;
	default:
		return -EINVAL;
	}

	iio_val = magn_state->magn_val_addr[offset];

	if (iio_val != NULL)
		*iio_val = *((u32 *)raw_data);
	else
		ret = -EINVAL;

	return ret;
}