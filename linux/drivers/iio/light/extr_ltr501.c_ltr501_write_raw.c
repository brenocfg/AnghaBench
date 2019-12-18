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
struct ltr501_data {int als_contr; int ps_contr; int /*<<< orphan*/  ps_period; int /*<<< orphan*/  als_period; int /*<<< orphan*/  lock_als; int /*<<< orphan*/  regmap; struct ltr501_chip_info* chip_info; } ;
struct ltr501_chip_info {int als_gain_mask; int als_gain_shift; int /*<<< orphan*/  ps_gain_tbl_size; int /*<<< orphan*/  ps_gain; int /*<<< orphan*/  als_gain_tbl_size; int /*<<< orphan*/  als_gain; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 132 
#define  IIO_CHAN_INFO_SAMP_FREQ 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int /*<<< orphan*/  LTR501_ALS_CONTR ; 
 int LTR501_CONTR_PS_GAIN_MASK ; 
 int LTR501_CONTR_PS_GAIN_SHIFT ; 
 int /*<<< orphan*/  LTR501_PS_CONTR ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ltr501_data* iio_priv (struct iio_dev*) ; 
 int ltr501_als_read_samp_freq (struct ltr501_data*,int*,int*) ; 
 int ltr501_als_write_samp_freq (struct ltr501_data*,int,int) ; 
 int ltr501_get_gain_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ltr501_ps_read_samp_freq (struct ltr501_data*,int*,int*) ; 
 int ltr501_ps_write_samp_freq (struct ltr501_data*,int,int) ; 
 int ltr501_set_it_time (struct ltr501_data*,int) ; 
 int ltr501_write_intr_prst (struct ltr501_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ltr501_write_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int val, int val2, long mask)
{
	struct ltr501_data *data = iio_priv(indio_dev);
	int i, ret, freq_val, freq_val2;
	struct ltr501_chip_info *info = data->chip_info;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_INTENSITY:
			i = ltr501_get_gain_index(info->als_gain,
						  info->als_gain_tbl_size,
						  val, val2);
			if (i < 0) {
				ret = -EINVAL;
				break;
			}

			data->als_contr &= ~info->als_gain_mask;
			data->als_contr |= i << info->als_gain_shift;

			ret = regmap_write(data->regmap, LTR501_ALS_CONTR,
					   data->als_contr);
			break;
		case IIO_PROXIMITY:
			i = ltr501_get_gain_index(info->ps_gain,
						  info->ps_gain_tbl_size,
						  val, val2);
			if (i < 0) {
				ret = -EINVAL;
				break;
			}
			data->ps_contr &= ~LTR501_CONTR_PS_GAIN_MASK;
			data->ps_contr |= i << LTR501_CONTR_PS_GAIN_SHIFT;

			ret = regmap_write(data->regmap, LTR501_PS_CONTR,
					   data->ps_contr);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;

	case IIO_CHAN_INFO_INT_TIME:
		switch (chan->type) {
		case IIO_INTENSITY:
			if (val != 0) {
				ret = -EINVAL;
				break;
			}
			mutex_lock(&data->lock_als);
			ret = ltr501_set_it_time(data, val2);
			mutex_unlock(&data->lock_als);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;

	case IIO_CHAN_INFO_SAMP_FREQ:
		switch (chan->type) {
		case IIO_INTENSITY:
			ret = ltr501_als_read_samp_freq(data, &freq_val,
							&freq_val2);
			if (ret < 0)
				break;

			ret = ltr501_als_write_samp_freq(data, val, val2);
			if (ret < 0)
				break;

			/* update persistence count when changing frequency */
			ret = ltr501_write_intr_prst(data, chan->type,
						     0, data->als_period);

			if (ret < 0)
				ret = ltr501_als_write_samp_freq(data, freq_val,
								 freq_val2);
			break;
		case IIO_PROXIMITY:
			ret = ltr501_ps_read_samp_freq(data, &freq_val,
						       &freq_val2);
			if (ret < 0)
				break;

			ret = ltr501_ps_write_samp_freq(data, val, val2);
			if (ret < 0)
				break;

			/* update persistence count when changing frequency */
			ret = ltr501_write_intr_prst(data, chan->type,
						     0, data->ps_period);

			if (ret < 0)
				ret = ltr501_ps_write_samp_freq(data, freq_val,
								freq_val2);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;

	default:
		ret = -EINVAL;
		break;
	}

	iio_device_release_direct_mode(indio_dev);
	return ret;
}