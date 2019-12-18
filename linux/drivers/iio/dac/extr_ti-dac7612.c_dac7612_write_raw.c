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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t channel; } ;
struct dac7612 {int* cache; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DAC7612_RESOLUTION ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 int dac7612_cmd_single (struct dac7612*,size_t,int) ; 
 struct dac7612* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dac7612_write_raw(struct iio_dev *iio_dev,
			     const struct iio_chan_spec *chan,
			     int val, int val2, long mask)
{
	struct dac7612 *priv = iio_priv(iio_dev);
	int ret;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	if ((val >= BIT(DAC7612_RESOLUTION)) || val < 0 || val2)
		return -EINVAL;

	if (val == priv->cache[chan->channel])
		return 0;

	mutex_lock(&iio_dev->mlock);
	ret = dac7612_cmd_single(priv, chan->channel, val);
	mutex_unlock(&iio_dev->mlock);

	return ret;
}