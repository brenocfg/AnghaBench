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
struct hp03_priv {int pressure; int temp; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int hp03_update_temp_pressure (struct hp03_priv*) ; 
 struct hp03_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp03_read_raw(struct iio_dev *indio_dev,
			 struct iio_chan_spec const *chan,
			 int *val, int *val2, long mask)
{
	struct hp03_priv *priv = iio_priv(indio_dev);
	int ret;

	mutex_lock(&priv->lock);
	ret = hp03_update_temp_pressure(priv);
	mutex_unlock(&priv->lock);

	if (ret)
		return ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_PRESSURE:
			*val = priv->pressure;
			return IIO_VAL_INT;
		case IIO_TEMP:
			*val = priv->temp;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_PRESSURE:
			*val = 0;
			*val2 = 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = 10;
			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}