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
struct max44000_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 long IIO_CHAN_INFO_INT_TIME ; 
 long IIO_CHAN_INFO_RAW ; 
 long IIO_CHAN_INFO_SCALE ; 
 scalar_t__ IIO_CURRENT ; 
 scalar_t__ IIO_LIGHT ; 
 int NSEC_PER_SEC ; 
 int USEC_PER_SEC ; 
 int find_closest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_closest_descending (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max44000_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  max44000_int_time_avail_ns_array ; 
 int /*<<< orphan*/  max44000_scale_avail_ulux_array ; 
 int max44000_write_alspga (struct max44000_data*,int) ; 
 int max44000_write_alstim (struct max44000_data*,int) ; 
 int max44000_write_led_current_raw (struct max44000_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max44000_write_raw(struct iio_dev *indio_dev,
			      struct iio_chan_spec const *chan,
			      int val, int val2, long mask)
{
	struct max44000_data *data = iio_priv(indio_dev);
	int ret;

	if (mask == IIO_CHAN_INFO_RAW && chan->type == IIO_CURRENT) {
		mutex_lock(&data->lock);
		ret = max44000_write_led_current_raw(data, val);
		mutex_unlock(&data->lock);
		return ret;
	} else if (mask == IIO_CHAN_INFO_INT_TIME && chan->type == IIO_LIGHT) {
		s64 valns = val * NSEC_PER_SEC + val2;
		int alstim = find_closest_descending(valns,
				max44000_int_time_avail_ns_array,
				ARRAY_SIZE(max44000_int_time_avail_ns_array));
		mutex_lock(&data->lock);
		ret = max44000_write_alstim(data, alstim);
		mutex_unlock(&data->lock);
		return ret;
	} else if (mask == IIO_CHAN_INFO_SCALE && chan->type == IIO_LIGHT) {
		s64 valus = val * USEC_PER_SEC + val2;
		int alspga = find_closest(valus,
				max44000_scale_avail_ulux_array,
				ARRAY_SIZE(max44000_scale_avail_ulux_array));
		mutex_lock(&data->lock);
		ret = max44000_write_alspga(data, alspga);
		mutex_unlock(&data->lock);
		return ret;
	}

	return -EINVAL;
}