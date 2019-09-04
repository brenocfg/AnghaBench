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
struct dev_rot_state {int /*<<< orphan*/  common_attributes; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HYSTERESIS 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int hid_sensor_write_raw_hyst_value (int /*<<< orphan*/ *,int,int) ; 
 int hid_sensor_write_samp_freq_value (int /*<<< orphan*/ *,int,int) ; 
 struct dev_rot_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int dev_rot_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct dev_rot_state *rot_state = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_write_samp_freq_value(
				&rot_state->common_attributes, val, val2);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		ret = hid_sensor_write_raw_hyst_value(
				&rot_state->common_attributes, val, val2);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}