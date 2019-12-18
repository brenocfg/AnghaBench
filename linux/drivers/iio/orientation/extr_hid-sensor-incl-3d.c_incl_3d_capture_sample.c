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
typedef  void* u32 ;
struct incl_3d_state {void** incl_val; } ;
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 size_t CHANNEL_SCAN_INDEX_X ; 
 size_t CHANNEL_SCAN_INDEX_Y ; 
 size_t CHANNEL_SCAN_INDEX_Z ; 
 int EINVAL ; 
#define  HID_USAGE_SENSOR_ORIENT_TILT_X 130 
#define  HID_USAGE_SENSOR_ORIENT_TILT_Y 129 
#define  HID_USAGE_SENSOR_ORIENT_TILT_Z 128 
 struct incl_3d_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int incl_3d_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct incl_3d_state *incl_state = iio_priv(indio_dev);
	int ret = 0;

	switch (usage_id) {
	case HID_USAGE_SENSOR_ORIENT_TILT_X:
		incl_state->incl_val[CHANNEL_SCAN_INDEX_X] = *(u32 *)raw_data;
	break;
	case HID_USAGE_SENSOR_ORIENT_TILT_Y:
		incl_state->incl_val[CHANNEL_SCAN_INDEX_Y] = *(u32 *)raw_data;
	break;
	case HID_USAGE_SENSOR_ORIENT_TILT_Z:
		incl_state->incl_val[CHANNEL_SCAN_INDEX_Z] = *(u32 *)raw_data;
	break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}