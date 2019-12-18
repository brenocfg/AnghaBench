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
struct vcnl4035_data {int als_it_val; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 128 
 int /*<<< orphan*/  VCNL4035_ALS_CONF ; 
 int /*<<< orphan*/  VCNL4035_ALS_IT_MASK ; 
 struct vcnl4035_data* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vcnl4035_set_pm_runtime_state (struct vcnl4035_data*,int) ; 

__attribute__((used)) static int vcnl4035_write_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int val, int val2, long mask)
{
	int ret;
	struct vcnl4035_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		if (val <= 0 || val > 800)
			return -EINVAL;

		ret = vcnl4035_set_pm_runtime_state(data, true);
		if  (ret < 0)
			return ret;

		ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
					 VCNL4035_ALS_IT_MASK,
					 val / 100);
		if (!ret)
			data->als_it_val = val / 100;

		vcnl4035_set_pm_runtime_state(data, false);
		return ret;
	default:
		return -EINVAL;
	}
}