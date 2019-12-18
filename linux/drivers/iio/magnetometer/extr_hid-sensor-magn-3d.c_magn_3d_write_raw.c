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
struct magn_3d_state {int /*<<< orphan*/  rot_attributes; int /*<<< orphan*/  magn_flux_attributes; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HYSTERESIS 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_MAGN 129 
#define  IIO_ROT 128 
 int hid_sensor_write_raw_hyst_value (int /*<<< orphan*/ *,int,int) ; 
 int hid_sensor_write_samp_freq_value (int /*<<< orphan*/ *,int,int) ; 
 struct magn_3d_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int magn_3d_write_raw(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val,
			       int val2,
			       long mask)
{
	struct magn_3d_state *magn_state = iio_priv(indio_dev);
	int ret = 0;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = hid_sensor_write_samp_freq_value(
				&magn_state->magn_flux_attributes, val, val2);
		break;
	case IIO_CHAN_INFO_HYSTERESIS:
		switch (chan->type) {
		case IIO_MAGN:
			ret = hid_sensor_write_raw_hyst_value(
				&magn_state->magn_flux_attributes, val, val2);
			break;
		case IIO_ROT:
			ret = hid_sensor_write_raw_hyst_value(
				&magn_state->rot_attributes, val, val2);
			break;
		default:
			ret = -EINVAL;
		}
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}