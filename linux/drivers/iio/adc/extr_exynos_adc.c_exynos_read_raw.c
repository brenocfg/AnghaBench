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
struct iio_dev {int /*<<< orphan*/  mlock; int /*<<< orphan*/  dev; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct exynos_adc {int value; TYPE_1__* data; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_hw ) (struct exynos_adc*) ;int /*<<< orphan*/  (* start_conv ) (struct exynos_adc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  EXYNOS_ADC_TIMEOUT ; 
 long IIO_CHAN_INFO_RAW ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct exynos_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct exynos_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct exynos_adc*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_read_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *chan,
				int *val,
				int *val2,
				long mask)
{
	struct exynos_adc *info = iio_priv(indio_dev);
	unsigned long timeout;
	int ret;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);
	reinit_completion(&info->completion);

	/* Select the channel to be used and Trigger conversion */
	if (info->data->start_conv)
		info->data->start_conv(info, chan->address);

	timeout = wait_for_completion_timeout(&info->completion,
					      EXYNOS_ADC_TIMEOUT);
	if (timeout == 0) {
		dev_warn(&indio_dev->dev, "Conversion timed out! Resetting\n");
		if (info->data->init_hw)
			info->data->init_hw(info);
		ret = -ETIMEDOUT;
	} else {
		*val = info->value;
		*val2 = 0;
		ret = IIO_VAL_INT;
	}

	mutex_unlock(&indio_dev->mlock);

	return ret;
}