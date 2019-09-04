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
struct iio_chan_spec {int dummy; } ;
struct bmc150_accel_data {int slope_thres; int slope_dur; scalar_t__ ev_enable_state; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int BMC150_ACCEL_SLOPE_DUR_MASK ; 
 int BMC150_ACCEL_SLOPE_THRES_MASK ; 
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_EV_INFO_PERIOD 129 
#define  IIO_EV_INFO_VALUE 128 
 struct bmc150_accel_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int bmc150_accel_write_event(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int val, int val2)
{
	struct bmc150_accel_data *data = iio_priv(indio_dev);

	if (data->ev_enable_state)
		return -EBUSY;

	switch (info) {
	case IIO_EV_INFO_VALUE:
		data->slope_thres = val & BMC150_ACCEL_SLOPE_THRES_MASK;
		break;
	case IIO_EV_INFO_PERIOD:
		data->slope_dur = val & BMC150_ACCEL_SLOPE_DUR_MASK;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}