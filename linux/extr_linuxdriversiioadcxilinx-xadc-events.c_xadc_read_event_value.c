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
struct xadc {int* threshold; int temp_hysteresis; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_INFO_HYSTERESIS 129 
#define  IIO_EV_INFO_VALUE 128 
 int IIO_VAL_INT ; 
 int XADC_THRESHOLD_VALUE_SHIFT ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 unsigned int xadc_get_threshold_offset (struct iio_chan_spec const*,int) ; 

int xadc_read_event_value(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, enum iio_event_type type,
	enum iio_event_direction dir, enum iio_event_info info,
	int *val, int *val2)
{
	unsigned int offset = xadc_get_threshold_offset(chan, dir);
	struct xadc *xadc = iio_priv(indio_dev);

	switch (info) {
	case IIO_EV_INFO_VALUE:
		*val = xadc->threshold[offset];
		break;
	case IIO_EV_INFO_HYSTERESIS:
		*val = xadc->temp_hysteresis;
		break;
	default:
		return -EINVAL;
	}

	*val >>= XADC_THRESHOLD_VALUE_SHIFT;

	return IIO_VAL_INT;
}