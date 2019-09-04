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
struct iio_dev {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct als_state {void** illum; } ;

/* Variables and functions */
 size_t CHANNEL_SCAN_INDEX_ILLUM ; 
 size_t CHANNEL_SCAN_INDEX_INTENSITY ; 
 int EINVAL ; 
#define  HID_USAGE_SENSOR_LIGHT_ILLUM 128 
 struct als_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (void*) ; 

__attribute__((used)) static int als_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id,
				size_t raw_len, char *raw_data,
				void *priv)
{
	struct iio_dev *indio_dev = platform_get_drvdata(priv);
	struct als_state *als_state = iio_priv(indio_dev);
	int ret = -EINVAL;
	u32 sample_data = *(u32 *)raw_data;

	switch (usage_id) {
	case HID_USAGE_SENSOR_LIGHT_ILLUM:
		als_state->illum[CHANNEL_SCAN_INDEX_INTENSITY] = sample_data;
		als_state->illum[CHANNEL_SCAN_INDEX_ILLUM] = sample_data;
		ret = 0;
		break;
	default:
		break;
	}

	return ret;
}