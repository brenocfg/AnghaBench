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
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct hid_time_state {struct rtc_time time_buf; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HID_USAGE_SENSOR_TIME_DAY 133 
#define  HID_USAGE_SENSOR_TIME_HOUR 132 
#define  HID_USAGE_SENSOR_TIME_MINUTE 131 
#define  HID_USAGE_SENSOR_TIME_MONTH 130 
#define  HID_USAGE_SENSOR_TIME_SECOND 129 
#define  HID_USAGE_SENSOR_TIME_YEAR 128 
 scalar_t__ hid_time_value (size_t,char*) ; 
 struct hid_time_state* platform_get_drvdata (void*) ; 

__attribute__((used)) static int hid_time_capture_sample(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id, size_t raw_len,
				char *raw_data, void *priv)
{
	struct hid_time_state *time_state = platform_get_drvdata(priv);
	struct rtc_time *time_buf = &time_state->time_buf;

	switch (usage_id) {
	case HID_USAGE_SENSOR_TIME_YEAR:
		/*
		 * The draft for HID-sensors (HUTRR39) currently doesn't define
		 * the range for the year attribute. Therefor we support
		 * 8 bit (0-99) and 16 or 32 bits (full) as size for the year.
		 */
		if (raw_len == 1) {
			time_buf->tm_year = *(u8 *)raw_data;
			if (time_buf->tm_year < 70)
				/* assume we are in 1970...2069 */
				time_buf->tm_year += 100;
		} else
			time_buf->tm_year =
				(int)hid_time_value(raw_len, raw_data)-1900;
		break;
	case HID_USAGE_SENSOR_TIME_MONTH:
		/* sensors are sending the month as 1-12, we need 0-11 */
		time_buf->tm_mon = (int)hid_time_value(raw_len, raw_data)-1;
		break;
	case HID_USAGE_SENSOR_TIME_DAY:
		time_buf->tm_mday = (int)hid_time_value(raw_len, raw_data);
		break;
	case HID_USAGE_SENSOR_TIME_HOUR:
		time_buf->tm_hour = (int)hid_time_value(raw_len, raw_data);
		break;
	case HID_USAGE_SENSOR_TIME_MINUTE:
		time_buf->tm_min = (int)hid_time_value(raw_len, raw_data);
		break;
	case HID_USAGE_SENSOR_TIME_SECOND:
		time_buf->tm_sec = (int)hid_time_value(raw_len, raw_data);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}