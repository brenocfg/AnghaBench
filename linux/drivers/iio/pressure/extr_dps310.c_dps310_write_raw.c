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
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
struct dps310_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_OVERSAMPLING_RATIO 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int dps310_set_pres_precision (struct dps310_data*,int) ; 
 int dps310_set_pres_samp_freq (struct dps310_data*,int) ; 
 int dps310_set_temp_precision (struct dps310_data*,int) ; 
 int dps310_set_temp_samp_freq (struct dps310_data*,int) ; 
 struct dps310_data* iio_priv (struct iio_dev*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dps310_write_raw(struct iio_dev *iio,
			    struct iio_chan_spec const *chan, int val,
			    int val2, long mask)
{
	int rc;
	struct dps310_data *data = iio_priv(iio);

	if (mutex_lock_interruptible(&data->lock))
		return -EINTR;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		switch (chan->type) {
		case IIO_PRESSURE:
			rc = dps310_set_pres_samp_freq(data, val);
			break;

		case IIO_TEMP:
			rc = dps310_set_temp_samp_freq(data, val);
			break;

		default:
			rc = -EINVAL;
			break;
		}
		break;

	case IIO_CHAN_INFO_OVERSAMPLING_RATIO:
		switch (chan->type) {
		case IIO_PRESSURE:
			rc = dps310_set_pres_precision(data, val);
			break;

		case IIO_TEMP:
			rc = dps310_set_temp_precision(data, val);
			break;

		default:
			rc = -EINVAL;
			break;
		}
		break;

	default:
		rc = -EINVAL;
		break;
	}

	mutex_unlock(&data->lock);
	return rc;
}