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
struct TYPE_2__ {unsigned int conv_mode; } ;
struct vf610_adc {TYPE_1__ adc_feature; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vf610_adc_calculate_rates (struct vf610_adc*) ; 
 int /*<<< orphan*/  vf610_adc_hw_init (struct vf610_adc*) ; 

__attribute__((used)) static int vf610_set_conversion_mode(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     unsigned int mode)
{
	struct vf610_adc *info = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	info->adc_feature.conv_mode = mode;
	vf610_adc_calculate_rates(info);
	vf610_adc_hw_init(info);
	mutex_unlock(&indio_dev->mlock);

	return 0;
}