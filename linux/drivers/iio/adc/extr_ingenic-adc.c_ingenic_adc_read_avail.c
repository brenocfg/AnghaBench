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
struct ingenic_adc {TYPE_1__* soc_data; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int battery_raw_avail_size; int* battery_raw_avail; int battery_scale_avail_size; int* battery_scale_avail; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_AVAIL_LIST ; 
 int IIO_AVAIL_RANGE ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 struct ingenic_adc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ingenic_adc_read_avail(struct iio_dev *iio_dev,
				  struct iio_chan_spec const *chan,
				  const int **vals,
				  int *type,
				  int *length,
				  long m)
{
	struct ingenic_adc *adc = iio_priv(iio_dev);

	switch (m) {
	case IIO_CHAN_INFO_RAW:
		*type = IIO_VAL_INT;
		*length = adc->soc_data->battery_raw_avail_size;
		*vals = adc->soc_data->battery_raw_avail;
		return IIO_AVAIL_RANGE;
	case IIO_CHAN_INFO_SCALE:
		*type = IIO_VAL_FRACTIONAL_LOG2;
		*length = adc->soc_data->battery_scale_avail_size;
		*vals = adc->soc_data->battery_scale_avail;
		return IIO_AVAIL_LIST;
	default:
		return -EINVAL;
	};
}