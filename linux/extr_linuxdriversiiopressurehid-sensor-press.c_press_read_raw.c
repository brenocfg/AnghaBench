#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  hsdev; } ;
struct TYPE_5__ {int report_id; int /*<<< orphan*/  logical_minimum; } ;
struct press_state {int scale_pre_decml; int scale_post_decml; int scale_precision; int value_offset; TYPE_2__ common_attributes; TYPE_1__ press_attr; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  scan_index; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  CHANNEL_SCAN_INDEX_PRESSURE 133 
 int EINVAL ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_PRESSURE ; 
#define  IIO_CHAN_INFO_HYSTERESIS 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  SENSOR_HUB_SYNC ; 
 int /*<<< orphan*/  hid_sensor_power_state (TYPE_2__*,int) ; 
 int hid_sensor_read_raw_hyst_value (TYPE_2__*,int*,int*) ; 
 int hid_sensor_read_samp_freq_value (TYPE_2__*,int*,int*) ; 
 struct press_state* iio_priv (struct iio_dev*) ; 
 int sensor_hub_input_attr_get_raw_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int press_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct press_state *press_state = iio_priv(indio_dev);
	int report_id = -1;
	u32 address;
	int ret_type;
	s32 min;

	*val = 0;
	*val2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->scan_index) {
		case  CHANNEL_SCAN_INDEX_PRESSURE:
			report_id = press_state->press_attr.report_id;
			min = press_state->press_attr.logical_minimum;
			address = HID_USAGE_SENSOR_ATMOSPHERIC_PRESSURE;
			break;
		default:
			report_id = -1;
			break;
		}
		if (report_id >= 0) {
			hid_sensor_power_state(&press_state->common_attributes,
						true);
			*val = sensor_hub_input_attr_get_raw_value(
				press_state->common_attributes.hsdev,
				HID_USAGE_SENSOR_PRESSURE, address,
				report_id,
				SENSOR_HUB_SYNC,
				min < 0);
			hid_sensor_power_state(&press_state->common_attributes,
						false);
		} else {
			*val = 0;
			return -EINVAL;
		}
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = press_state->scale_pre_decml;
		*val2 = press_state->scale_post_decml;
		ret_type = press_state->scale_precision;
		break;
	case IIO_CHAN_INFO_OFFSET:
		*val = press_state->value_offset;
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_read_samp_freq_value(
				&press_state->common_attributes, val, val2);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_read_raw_hyst_value(
				&press_state->common_attributes, val, val2);
		break;
	default:
		ret_type = -EINVAL;
		break;
	}

	return ret_type;
}