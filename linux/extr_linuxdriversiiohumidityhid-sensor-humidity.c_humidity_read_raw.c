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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  hsdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  logical_minimum; int /*<<< orphan*/  report_id; } ;
struct hid_humidity_state {int scale_pre_decml; int scale_post_decml; int scale_precision; int value_offset; TYPE_2__ common_attributes; TYPE_1__ humidity_attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_ATMOSPHERIC_HUMIDITY ; 
 int /*<<< orphan*/  HID_USAGE_SENSOR_HUMIDITY ; 
#define  IIO_CHAN_INFO_HYSTERESIS 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_HUMIDITYRELATIVE ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  SENSOR_HUB_SYNC ; 
 int /*<<< orphan*/  hid_sensor_power_state (TYPE_2__*,int) ; 
 int hid_sensor_read_raw_hyst_value (TYPE_2__*,int*,int*) ; 
 int hid_sensor_read_samp_freq_value (TYPE_2__*,int*,int*) ; 
 struct hid_humidity_state* iio_priv (struct iio_dev*) ; 
 int sensor_hub_input_attr_get_raw_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int humidity_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val, int *val2, long mask)
{
	struct hid_humidity_state *humid_st = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type != IIO_HUMIDITYRELATIVE)
			return -EINVAL;
		hid_sensor_power_state(&humid_st->common_attributes, true);
		*val = sensor_hub_input_attr_get_raw_value(
				humid_st->common_attributes.hsdev,
				HID_USAGE_SENSOR_HUMIDITY,
				HID_USAGE_SENSOR_ATMOSPHERIC_HUMIDITY,
				humid_st->humidity_attr.report_id,
				SENSOR_HUB_SYNC,
				humid_st->humidity_attr.logical_minimum < 0);
		hid_sensor_power_state(&humid_st->common_attributes, false);

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:
		*val = humid_st->scale_pre_decml;
		*val2 = humid_st->scale_post_decml;

		return humid_st->scale_precision;

	case IIO_CHAN_INFO_OFFSET:
		*val = humid_st->value_offset;

		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SAMP_FREQ:
		return hid_sensor_read_samp_freq_value(
				&humid_st->common_attributes, val, val2);

	case IIO_CHAN_INFO_HYSTERESIS:
		return hid_sensor_read_raw_hyst_value(
				&humid_st->common_attributes, val, val2);

	default:
		return -EINVAL;
	}
}