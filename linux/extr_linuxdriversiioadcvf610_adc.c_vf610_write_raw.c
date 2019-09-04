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
struct TYPE_2__ {int sample_rate; } ;
struct vf610_adc {int* sample_freq_avail; TYPE_1__ adc_feature; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  vf610_adc_sample_set (struct vf610_adc*) ; 

__attribute__((used)) static int vf610_write_raw(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int val,
			int val2,
			long mask)
{
	struct vf610_adc *info = iio_priv(indio_dev);
	int i;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		for (i = 0;
			i < ARRAY_SIZE(info->sample_freq_avail);
			i++)
			if (val == info->sample_freq_avail[i]) {
				info->adc_feature.sample_rate = i;
				vf610_adc_sample_set(info);
				return 0;
			}
		break;

	default:
		break;
	}

	return -EINVAL;
}