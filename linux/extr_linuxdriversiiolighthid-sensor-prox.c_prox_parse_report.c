#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ index; int /*<<< orphan*/  report_id; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {TYPE_2__ sensitivity; } ;
struct prox_state {TYPE_1__ common_attributes; TYPE_2__ prox_attr; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_SCAN_INDEX_PRESENCE ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS ; 
 int HID_USAGE_SENSOR_DATA_PRESENCE ; 
 int HID_USAGE_SENSOR_HUMAN_PRESENCE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prox_adjust_channel_bit_mask (struct iio_chan_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,unsigned int,int,TYPE_2__*) ; 

__attribute__((used)) static int prox_parse_report(struct platform_device *pdev,
				struct hid_sensor_hub_device *hsdev,
				struct iio_chan_spec *channels,
				unsigned usage_id,
				struct prox_state *st)
{
	int ret;

	ret = sensor_hub_input_get_attribute_info(hsdev, HID_INPUT_REPORT,
			usage_id,
			HID_USAGE_SENSOR_HUMAN_PRESENCE,
			&st->prox_attr);
	if (ret < 0)
		return ret;
	prox_adjust_channel_bit_mask(channels, CHANNEL_SCAN_INDEX_PRESENCE,
					st->prox_attr.size);

	dev_dbg(&pdev->dev, "prox %x:%x\n", st->prox_attr.index,
			st->prox_attr.report_id);

	/* Set Sensitivity field ids, when there is no individual modifier */
	if (st->common_attributes.sensitivity.index < 0) {
		sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOR_DATA_PRESENCE,
			&st->common_attributes.sensitivity);
		dev_dbg(&pdev->dev, "Sensitivity index:report %d:%d\n",
			st->common_attributes.sensitivity.index,
			st->common_attributes.sensitivity.report_id);
	}
	if (st->common_attributes.sensitivity.index < 0)
		sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOR_HUMAN_PRESENCE,
			&st->common_attributes.sensitivity);

	return ret;
}