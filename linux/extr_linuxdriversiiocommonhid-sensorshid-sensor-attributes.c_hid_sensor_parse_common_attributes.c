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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u32 ;
struct hid_sensor_hub_device {int /*<<< orphan*/  hdev; } ;
struct hid_sensor_hub_attribute_info {int logical_minimum; scalar_t__ index; scalar_t__ report_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  report_id; int /*<<< orphan*/  index; } ;
struct hid_sensor_common {int raw_hystersis; int timestamp_ns_scale; struct hid_sensor_hub_attribute_info power_state; struct hid_sensor_hub_attribute_info sensitivity; struct hid_sensor_hub_attribute_info report_state; TYPE_1__ poll; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PROP_REPORT_STATE ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PROP_SENSITIVITY_ABS ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PROY_POWER_STATE ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_TIME_TIMESTAMP ; 
 int /*<<< orphan*/  hid_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hid_sensor_format_scale (int /*<<< orphan*/ ,struct hid_sensor_hub_attribute_info*,int*,int*) ; 
 int /*<<< orphan*/  hid_sensor_get_report_latency_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,struct hid_sensor_common*) ; 
 int /*<<< orphan*/  hid_sensor_get_reporting_interval (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,struct hid_sensor_common*) ; 
 int sensor_hub_get_feature (struct hid_sensor_hub_device*,scalar_t__,scalar_t__,int,scalar_t__*) ; 
 int /*<<< orphan*/  sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hid_sensor_hub_attribute_info*) ; 

int hid_sensor_parse_common_attributes(struct hid_sensor_hub_device *hsdev,
					u32 usage_id,
					struct hid_sensor_common *st)
{

	struct hid_sensor_hub_attribute_info timestamp;
	s32 value;
	int ret;

	hid_sensor_get_reporting_interval(hsdev, usage_id, st);

	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROP_REPORT_STATE,
					&st->report_state);

	sensor_hub_input_get_attribute_info(hsdev,
					HID_FEATURE_REPORT, usage_id,
					HID_USAGE_SENSOR_PROY_POWER_STATE,
					&st->power_state);

	st->power_state.logical_minimum = 1;
	st->report_state.logical_minimum = 1;

	sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_PROP_SENSITIVITY_ABS,
			 &st->sensitivity);

	st->raw_hystersis = -1;

	sensor_hub_input_get_attribute_info(hsdev,
					    HID_INPUT_REPORT, usage_id,
					    HID_USAGE_SENSOR_TIME_TIMESTAMP,
					    &timestamp);
	if (timestamp.index >= 0 && timestamp.report_id) {
		int val0, val1;

		hid_sensor_format_scale(HID_USAGE_SENSOR_TIME_TIMESTAMP,
					&timestamp, &val0, &val1);
		st->timestamp_ns_scale = val0;
	} else
		st->timestamp_ns_scale = 1000000000;

	hid_sensor_get_report_latency_info(hsdev, usage_id, st);

	hid_dbg(hsdev->hdev, "common attributes: %x:%x, %x:%x, %x:%x %x:%x %x:%x\n",
		st->poll.index, st->poll.report_id,
		st->report_state.index, st->report_state.report_id,
		st->power_state.index, st->power_state.report_id,
		st->sensitivity.index, st->sensitivity.report_id,
		timestamp.index, timestamp.report_id);

	ret = sensor_hub_get_feature(hsdev,
				st->power_state.report_id,
				st->power_state.index, sizeof(value), &value);
	if (ret < 0)
		return ret;
	if (value < 0)
		return -EINVAL;

	return 0;
}