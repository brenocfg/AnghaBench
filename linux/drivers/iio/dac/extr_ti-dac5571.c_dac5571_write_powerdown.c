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
struct dac5571_data {int powerdown; int (* dac5571_pwrdwn ) (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* dac5571_cmd ) (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; int /*<<< orphan*/ * val; int /*<<< orphan*/  powerdown_mode; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAC5571_POWERDOWN (int /*<<< orphan*/ ) ; 
 struct dac5571_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct dac5571_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t dac5571_write_powerdown(struct iio_dev *indio_dev,
				       uintptr_t private,
				       const struct iio_chan_spec *chan,
				       const char *buf, size_t len)
{
	struct dac5571_data *data = iio_priv(indio_dev);
	bool powerdown;
	int ret;

	ret = strtobool(buf, &powerdown);
	if (ret)
		return ret;

	if (data->powerdown == powerdown)
		return len;

	mutex_lock(&data->lock);
	if (powerdown)
		ret = data->dac5571_pwrdwn(data, chan->channel,
			    DAC5571_POWERDOWN(data->powerdown_mode));
	else
		ret = data->dac5571_cmd(data, chan->channel, data->val[0]);
	if (ret)
		goto out;

	data->powerdown = powerdown;

 out:
	mutex_unlock(&data->lock);

	return ret ? ret : len;
}