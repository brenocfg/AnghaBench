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
struct iio_chan_spec {scalar_t__ type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_EV_TYPE_THRESH ; 
 scalar_t__ IIO_LIGHT ; 
 int IIO_VAL_FRACTIONAL ; 
 int MAX44009_SCALE_DENOMINATOR ; 
 int MAX44009_SCALE_NUMERATOR ; 
 int max44009_read_threshold (struct iio_dev*,int) ; 

__attribute__((used)) static int max44009_read_event_value(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     enum iio_event_info info,
				     int *val, int *val2)
{
	int ret;
	int threshold;

	if (chan->type != IIO_LIGHT || type != IIO_EV_TYPE_THRESH)
		return -EINVAL;

	ret = max44009_read_threshold(indio_dev, dir);
	if (ret < 0)
		return ret;
	threshold = ret;

	*val = threshold * MAX44009_SCALE_NUMERATOR;
	*val2 = MAX44009_SCALE_DENOMINATOR;

	return IIO_VAL_FRACTIONAL;
}