#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ index; int /*<<< orphan*/  report_id; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_2__ sensitivity; } ;
struct press_state {TYPE_1__ common_attributes; int /*<<< orphan*/  scale_post_decml; int /*<<< orphan*/  scale_pre_decml; TYPE_2__ press_attr; int /*<<< orphan*/  scale_precision; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_SCAN_INDEX_PRESSURE ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE ; 
 int HID_USAGE_SENSOR_DATA_ATMOSPHERIC_PRESSURE ; 
 int HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PRESSURE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_sensor_format_scale (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  press_adjust_channel_bit_mask (struct iio_chan_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,unsigned int,int,TYPE_2__*) ; 

__attribute__((used)) static int press_parse_report(struct platform_device *pdev,
				struct hid_sensor_hub_device *hsdev,
				struct iio_chan_spec *channels,
				unsigned usage_id,
				struct press_state *st)
{
	int ret;

	ret = sensor_hub_input_get_attribute_info(hsdev, HID_INPUT_REPORT,
			usage_id,
			HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE,
			&st->press_attr);
	if (ret < 0)
		return ret;
	press_adjust_channel_bit_mask(channels, CHANNEL_SCAN_INDEX_PRESSURE,
					st->press_attr.size);

	dev_dbg(&pdev->dev, "press %x:%x\n", st->press_attr.index,
			st->press_attr.report_id);

	st->scale_precision = hid_sensor_format_scale(
				HID_USAGE_SENSOR_PRESSURE,
				&st->press_attr,
				&st->scale_pre_decml, &st->scale_post_decml);

	/* Set Sensitivity field ids, when there is no individual modifier */
	if (st->common_attributes.sensitivity.index < 0) {
		sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOR_DATA_ATMOSPHERIC_PRESSURE,
			&st->common_attributes.sensitivity);
		dev_dbg(&pdev->dev, "Sensitivity index:report %d:%d\n",
			st->common_attributes.sensitivity.index,
			st->common_attributes.sensitivity.report_id);
	}
	return ret;
}