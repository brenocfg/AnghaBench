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
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct dac5571_data {unsigned int powerdown_mode; int (* dac5571_pwrdwn ) (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; scalar_t__ powerdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC5571_POWERDOWN (unsigned int) ; 
 struct dac5571_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dac5571_set_powerdown_mode(struct iio_dev *indio_dev,
				      const struct iio_chan_spec *chan,
				      unsigned int mode)
{
	struct dac5571_data *data = iio_priv(indio_dev);
	int ret = 0;

	if (data->powerdown_mode == mode)
		return 0;

	mutex_lock(&data->lock);
	if (data->powerdown) {
		ret = data->dac5571_pwrdwn(data, chan->channel,
					   DAC5571_POWERDOWN(mode));
		if (ret)
			goto out;
	}
	data->powerdown_mode = mode;

 out:
	mutex_unlock(&data->lock);

	return ret;
}