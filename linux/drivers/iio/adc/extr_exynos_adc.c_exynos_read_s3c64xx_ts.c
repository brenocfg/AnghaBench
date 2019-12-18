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
struct exynos_adc {int read_ts; int ts_x; int ts_y; TYPE_1__* data; int /*<<< orphan*/  completion; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_hw ) (struct exynos_adc*) ;int /*<<< orphan*/  (* start_conv ) (struct exynos_adc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_S3C2410_MUX_TS ; 
 int ADC_S3C2410_TSC_PULL_UP_DISABLE ; 
 int ADC_TSC_AUTOPST ; 
 int /*<<< orphan*/  ADC_V1_TSC (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  EXYNOS_ADC_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct exynos_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct exynos_adc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct exynos_adc*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_read_s3c64xx_ts(struct iio_dev *indio_dev, int *x, int *y)
{
	struct exynos_adc *info = iio_priv(indio_dev);
	unsigned long timeout;
	int ret;

	mutex_lock(&indio_dev->mlock);
	info->read_ts = true;

	reinit_completion(&info->completion);

	writel(ADC_S3C2410_TSC_PULL_UP_DISABLE | ADC_TSC_AUTOPST,
	       ADC_V1_TSC(info->regs));

	/* Select the ts channel to be used and Trigger conversion */
	info->data->start_conv(info, ADC_S3C2410_MUX_TS);

	timeout = wait_for_completion_timeout(&info->completion,
					      EXYNOS_ADC_TIMEOUT);
	if (timeout == 0) {
		dev_warn(&indio_dev->dev, "Conversion timed out! Resetting\n");
		if (info->data->init_hw)
			info->data->init_hw(info);
		ret = -ETIMEDOUT;
	} else {
		*x = info->ts_x;
		*y = info->ts_y;
		ret = 0;
	}

	info->read_ts = false;
	mutex_unlock(&indio_dev->mlock);

	return ret;
}