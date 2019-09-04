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
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 int /*<<< orphan*/  iio_priv (struct iio_dev*) ; 
 int ltr501_read_intr_prst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ltr501_read_thresh (struct iio_dev*,struct iio_chan_spec const*,int,int,int,int*,int*) ; 

__attribute__((used)) static int ltr501_read_event(struct iio_dev *indio_dev,
			     const struct iio_chan_spec *chan,
			     enum iio_event_type type,
			     enum iio_event_direction dir,
			     enum iio_event_info info,
			     int *val, int *val2)
{
	int ret;

	switch (info) {
	case IIO_EV_INFO_VALUE:
		return ltr501_read_thresh(indio_dev, chan, type, dir,
					  info, val, val2);
	case IIO_EV_INFO_PERIOD:
		ret = ltr501_read_intr_prst(iio_priv(indio_dev),
					    chan->type, val2);
		*val = *val2 / 1000000;
		*val2 = *val2 % 1000000;
		return ret;
	default:
		return -EINVAL;
	}

	return -EINVAL;
}