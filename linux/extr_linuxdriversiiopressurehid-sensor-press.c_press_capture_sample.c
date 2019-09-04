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
struct press_state {int /*<<< orphan*/  press_data; } ;
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE 128 
 struct press_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int press_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct press_state *press_state = iio_priv(indio_dev);
	int ret = -EINVAL;

	switch (usage_id) {
	case HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE:
		press_state->press_data = *(u32 *)raw_data;
		ret = 0;
		break;
	default:
		break;
	}

	return ret;
}