#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct ads124s_private {int /*<<< orphan*/  lock; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS124S08_INPUT_MUX ; 
 int /*<<< orphan*/  ADS124S08_START_CONV ; 
 int /*<<< orphan*/  ADS124S08_STOP_CONV ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int ads124s_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int ads124s_write_cmd (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int ads124s_write_reg (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ads124s_private* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ads124s_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2, long m)
{
	struct ads124s_private *priv = iio_priv(indio_dev);
	int ret;

	mutex_lock(&priv->lock);
	switch (m) {
	case IIO_CHAN_INFO_RAW:
		ret = ads124s_write_reg(indio_dev, ADS124S08_INPUT_MUX,
					chan->channel);
		if (ret) {
			dev_err(&priv->spi->dev, "Set ADC CH failed\n");
			goto out;
		}

		ret = ads124s_write_cmd(indio_dev, ADS124S08_START_CONV);
		if (ret) {
			dev_err(&priv->spi->dev, "Start conversions failed\n");
			goto out;
		}

		ret = ads124s_read(indio_dev, chan->channel);
		if (ret < 0) {
			dev_err(&priv->spi->dev, "Read ADC failed\n");
			goto out;
		}

		*val = ret;

		ret = ads124s_write_cmd(indio_dev, ADS124S08_STOP_CONV);
		if (ret) {
			dev_err(&priv->spi->dev, "Stop conversions failed\n");
			goto out;
		}

		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		break;
	}
out:
	mutex_unlock(&priv->lock);
	return ret;
}