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
struct incl_3d_state {int scale_pre_decml; int scale_post_decml; int scale_precision; int value_offset; TYPE_2__ common_attributes; TYPE_1__* incl; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int report_id; int /*<<< orphan*/  logical_minimum; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_INCLINOMETER_3D ; 
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
 struct incl_3d_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/ * incl_3d_addresses ; 
 int sensor_hub_input_attr_get_raw_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int incl_3d_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct incl_3d_state *incl_state = iio_priv(indio_dev);
	int report_id = -1;
	u32 address;
	int ret_type;
	s32 min;

	*val = 0;
	*val2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		hid_sensor_power_state(&incl_state->common_attributes, true);
		report_id = incl_state->incl[chan->scan_index].report_id;
		min = incl_state->incl[chan->scan_index].logical_minimum;
		address = incl_3d_addresses[chan->scan_index];
		if (report_id >= 0)
			*val = sensor_hub_input_attr_get_raw_value(
				incl_state->common_attributes.hsdev,
				HID_USAGE_SENSOR_INCLINOMETER_3D, address,
				report_id,
				SENSOR_HUB_SYNC,
				min < 0);
		else {
			hid_sensor_power_state(&incl_state->common_attributes,
						false);
			return -EINVAL;
		}
		hid_sensor_power_state(&incl_state->common_attributes, false);
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = incl_state->scale_pre_decml;
		*val2 = incl_state->scale_post_decml;
		ret_type = incl_state->scale_precision;
		break;
	case IIO_CHAN_INFO_OFFSET:
		*val = incl_state->value_offset;
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_read_samp_freq_value(
			&incl_state->common_attributes, val, val2);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_read_raw_hyst_value(
			&incl_state->common_attributes, val, val2);
		break;
	default:
		ret_type = -EINVAL;
		break;
	}

	return ret_type;
}