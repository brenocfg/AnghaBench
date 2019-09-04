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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; } ;
struct hid_sensor_hub_device {int /*<<< orphan*/  usage; } ;
struct TYPE_6__ {struct hid_sensor_hub_device* hsdev; } ;
struct accel_3d_state {int scale_pre_decml; int scale_post_decml; int scale_precision; int value_offset; TYPE_2__ common_attributes; TYPE_1__* accel; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int report_id; int /*<<< orphan*/  logical_minimum; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HYSTERESIS 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  SENSOR_HUB_SYNC ; 
 int /*<<< orphan*/ * accel_3d_addresses ; 
 int /*<<< orphan*/  hid_sensor_power_state (TYPE_2__*,int) ; 
 int hid_sensor_read_raw_hyst_value (TYPE_2__*,int*,int*) ; 
 int hid_sensor_read_samp_freq_value (TYPE_2__*,int*,int*) ; 
 struct accel_3d_state* iio_priv (struct iio_dev*) ; 
 int sensor_hub_input_attr_get_raw_value (struct hid_sensor_hub_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int accel_3d_read_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int *val, int *val2,
			      long mask)
{
	struct accel_3d_state *accel_state = iio_priv(indio_dev);
	int report_id = -1;
	u32 address;
	int ret_type;
	s32 min;
	struct hid_sensor_hub_device *hsdev =
					accel_state->common_attributes.hsdev;

	*val = 0;
	*val2 = 0;
	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		hid_sensor_power_state(&accel_state->common_attributes, true);
		report_id = accel_state->accel[chan->scan_index].report_id;
		min = accel_state->accel[chan->scan_index].logical_minimum;
		address = accel_3d_addresses[chan->scan_index];
		if (report_id >= 0)
			*val = sensor_hub_input_attr_get_raw_value(
					accel_state->common_attributes.hsdev,
					hsdev->usage, address, report_id,
					SENSOR_HUB_SYNC,
					min < 0);
		else {
			*val = 0;
			hid_sensor_power_state(&accel_state->common_attributes,
						 false);
			return -EINVAL;
		}
		hid_sensor_power_state(&accel_state->common_attributes, false);
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		*val = accel_state->scale_pre_decml;
		*val2 = accel_state->scale_post_decml;
		ret_type = accel_state->scale_precision;
		break;
	case IIO_CHAN_INFO_OFFSET:
		*val = accel_state->value_offset;
		ret_type = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_read_samp_freq_value(
			&accel_state->common_attributes, val, val2);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_read_raw_hyst_value(
			&accel_state->common_attributes, val, val2);
		break;
	default:
		ret_type = -EINVAL;
		break;
	}

	return ret_type;
}