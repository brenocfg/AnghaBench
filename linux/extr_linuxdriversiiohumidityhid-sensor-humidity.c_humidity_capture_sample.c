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
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct hid_humidity_state {int /*<<< orphan*/  humidity_data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  HID_USAGE_SENSOR_ATMOSPHERIC_HUMIDITY 128 
 struct hid_humidity_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int humidity_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned int usage_id, size_t raw_len,
				char *raw_data, void *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct hid_humidity_state *humid_st = iio_priv(indio_dev);

	switch (usage_id) {
	case HID_USAGE_SENSOR_ATMOSPHERIC_HUMIDITY:
		humid_st->humidity_data = *(s32 *)raw_data;

		return 0;
	default:
		return -EINVAL;
	}
}