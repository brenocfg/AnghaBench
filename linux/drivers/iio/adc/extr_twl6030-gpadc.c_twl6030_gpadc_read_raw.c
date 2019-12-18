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
struct twl6030_gpadc_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_complete; int /*<<< orphan*/  dev; TYPE_1__* pdata; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int (* start_conversion ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ETIMEDOUT ; 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct twl6030_gpadc_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int twl6030_gpadc_get_processed (struct twl6030_gpadc_data*,int /*<<< orphan*/ ,int*) ; 
 int twl6030_gpadc_get_raw (struct twl6030_gpadc_data*,int /*<<< orphan*/ ,int*) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030_gpadc_read_raw(struct iio_dev *indio_dev,
			     const struct iio_chan_spec *chan,
			     int *val, int *val2, long mask)
{
	struct twl6030_gpadc_data *gpadc = iio_priv(indio_dev);
	int ret;
	long timeout;

	mutex_lock(&gpadc->lock);

	ret = gpadc->pdata->start_conversion(chan->channel);
	if (ret) {
		dev_err(gpadc->dev, "failed to start conversion\n");
		goto err;
	}
	/* wait for conversion to complete */
	timeout = wait_for_completion_interruptible_timeout(
				&gpadc->irq_complete, msecs_to_jiffies(5000));
	if (timeout == 0) {
		ret = -ETIMEDOUT;
		goto err;
	} else if (timeout < 0) {
		ret = -EINTR;
		goto err;
	}

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = twl6030_gpadc_get_raw(gpadc, chan->channel, val);
		ret = ret ? -EIO : IIO_VAL_INT;
		break;

	case IIO_CHAN_INFO_PROCESSED:
		ret = twl6030_gpadc_get_processed(gpadc, chan->channel, val);
		ret = ret ? -EIO : IIO_VAL_INT;
		break;

	default:
		break;
	}
err:
	mutex_unlock(&gpadc->lock);

	return ret;
}