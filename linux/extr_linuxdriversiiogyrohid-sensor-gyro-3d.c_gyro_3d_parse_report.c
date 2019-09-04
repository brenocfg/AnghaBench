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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int dummy; } ;
struct hid_sensor_hub_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ index; int /*<<< orphan*/  report_id; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_2__ sensitivity; } ;
struct gyro_3d_state {TYPE_1__ common_attributes; int /*<<< orphan*/  scale_post_decml; int /*<<< orphan*/  scale_pre_decml; TYPE_2__* gyro; int /*<<< orphan*/  scale_precision; } ;

/* Variables and functions */
 int CHANNEL_SCAN_INDEX_X ; 
 int CHANNEL_SCAN_INDEX_Z ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int HID_USAGE_SENSOR_ANGL_VELOCITY_X_AXIS ; 
 int HID_USAGE_SENSOR_DATA_ANGL_VELOCITY ; 
 int HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_GYRO_3D ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gyro_3d_adjust_channel_bit_mask (struct iio_chan_spec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_sensor_format_scale (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sensor_hub_input_get_attribute_info (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,unsigned int,int,TYPE_2__*) ; 

__attribute__((used)) static int gyro_3d_parse_report(struct platform_device *pdev,
				struct hid_sensor_hub_device *hsdev,
				struct iio_chan_spec *channels,
				unsigned usage_id,
				struct gyro_3d_state *st)
{
	int ret;
	int i;

	for (i = 0; i <= CHANNEL_SCAN_INDEX_Z; ++i) {
		ret = sensor_hub_input_get_attribute_info(hsdev,
				HID_INPUT_REPORT,
				usage_id,
				HID_USAGE_SENSOR_ANGL_VELOCITY_X_AXIS + i,
				&st->gyro[CHANNEL_SCAN_INDEX_X + i]);
		if (ret < 0)
			break;
		gyro_3d_adjust_channel_bit_mask(channels,
				CHANNEL_SCAN_INDEX_X + i,
				st->gyro[CHANNEL_SCAN_INDEX_X + i].size);
	}
	dev_dbg(&pdev->dev, "gyro_3d %x:%x, %x:%x, %x:%x\n",
			st->gyro[0].index,
			st->gyro[0].report_id,
			st->gyro[1].index, st->gyro[1].report_id,
			st->gyro[2].index, st->gyro[2].report_id);

	st->scale_precision = hid_sensor_format_scale(
				HID_USAGE_SENSOR_GYRO_3D,
				&st->gyro[CHANNEL_SCAN_INDEX_X],
				&st->scale_pre_decml, &st->scale_post_decml);

	/* Set Sensitivity field ids, when there is no individual modifier */
	if (st->common_attributes.sensitivity.index < 0) {
		sensor_hub_input_get_attribute_info(hsdev,
			HID_FEATURE_REPORT, usage_id,
			HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS |
			HID_USAGE_SENSOR_DATA_ANGL_VELOCITY,
			&st->common_attributes.sensitivity);
		dev_dbg(&pdev->dev, "Sensitivity index:report %d:%d\n",
			st->common_attributes.sensitivity.index,
			st->common_attributes.sensitivity.report_id);
	}
	return ret;
}