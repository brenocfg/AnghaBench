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
struct ltr501_data {unsigned long als_period; unsigned long ps_period; int /*<<< orphan*/  lock_ps; int /*<<< orphan*/  reg_ps_prst; int /*<<< orphan*/  lock_als; int /*<<< orphan*/  reg_als_prst; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned long,int) ; 
 int EINVAL ; 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int ltr501_als_read_samp_period (struct ltr501_data*,int*) ; 
 int ltr501_ps_read_samp_period (struct ltr501_data*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ltr501_write_intr_prst(struct ltr501_data *data,
				  enum iio_chan_type type,
				  int val, int val2)
{
	int ret, samp_period, new_val;
	unsigned long period;

	if (val < 0 || val2 < 0)
		return -EINVAL;

	/* period in microseconds */
	period = ((val * 1000000) + val2);

	switch (type) {
	case IIO_INTENSITY:
		ret = ltr501_als_read_samp_period(data, &samp_period);
		if (ret < 0)
			return ret;

		/* period should be atleast equal to sampling period */
		if (period < samp_period)
			return -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		if (new_val < 0 || new_val > 0x0f)
			return -EINVAL;

		mutex_lock(&data->lock_als);
		ret = regmap_field_write(data->reg_als_prst, new_val);
		mutex_unlock(&data->lock_als);
		if (ret >= 0)
			data->als_period = period;

		return ret;
	case IIO_PROXIMITY:
		ret = ltr501_ps_read_samp_period(data, &samp_period);
		if (ret < 0)
			return ret;

		/* period should be atleast equal to rate */
		if (period < samp_period)
			return -EINVAL;

		new_val = DIV_ROUND_UP(period, samp_period);
		if (new_val < 0 || new_val > 0x0f)
			return -EINVAL;

		mutex_lock(&data->lock_ps);
		ret = regmap_field_write(data->reg_ps_prst, new_val);
		mutex_unlock(&data->lock_ps);
		if (ret >= 0)
			data->ps_period = period;

		return ret;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}