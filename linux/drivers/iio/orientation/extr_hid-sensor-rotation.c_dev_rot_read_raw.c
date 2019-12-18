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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct dev_rot_state {int* sampled_vals; int scale_pre_decml; int scale_post_decml; int scale_precision; int value_offset; int /*<<< orphan*/  common_attributes; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HYSTERESIS 132 
#define  IIO_CHAN_INFO_OFFSET 131 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_MULTIPLE ; 
 int hid_sensor_read_raw_hyst_value (int /*<<< orphan*/ *,int*,int*) ; 
 int hid_sensor_read_samp_freq_value (int /*<<< orphan*/ *,int*,int*) ; 
 struct dev_rot_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int dev_rot_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int size, int *vals, int *val_len,
				long mask)
{
	struct dev_rot_state *rot_state = iio_priv(indio_dev);
	int ret_type;
	int i;

	vals[0] = 0;
	vals[1] = 0;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (size >= 4) {
			for (i = 0; i < 4; ++i)
				vals[i] = rot_state->sampled_vals[i];
			ret_type = IIO_VAL_INT_MULTIPLE;
			*val_len =  4;
		} else
			ret_type = -EINVAL;
		break;
	case IIO_CHAN_INFO_SCALE:
		vals[0] = rot_state->scale_pre_decml;
		vals[1] = rot_state->scale_post_decml;
		return rot_state->scale_precision;

	case IIO_CHAN_INFO_OFFSET:
		*vals = rot_state->value_offset;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SAMP_FREQ:
		ret_type = hid_sensor_read_samp_freq_value(
			&rot_state->common_attributes, &vals[0], &vals[1]);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		ret_type = hid_sensor_read_raw_hyst_value(
			&rot_state->common_attributes, &vals[0], &vals[1]);
		break;
	default:
		ret_type = -EINVAL;
		break;
	}

	return ret_type;
}