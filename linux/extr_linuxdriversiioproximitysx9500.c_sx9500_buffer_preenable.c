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
struct sx9500_data {int /*<<< orphan*/  mutex; } ;
struct iio_dev {int /*<<< orphan*/  active_scan_mask; } ;

/* Variables and functions */
 int SX9500_NUM_CHANNELS ; 
 struct sx9500_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx9500_dec_chan_users (struct sx9500_data*,int) ; 
 int sx9500_inc_chan_users (struct sx9500_data*,int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sx9500_buffer_preenable(struct iio_dev *indio_dev)
{
	struct sx9500_data *data = iio_priv(indio_dev);
	int ret = 0, i;

	mutex_lock(&data->mutex);

	for (i = 0; i < SX9500_NUM_CHANNELS; i++)
		if (test_bit(i, indio_dev->active_scan_mask)) {
			ret = sx9500_inc_chan_users(data, i);
			if (ret)
				break;
		}

	if (ret)
		for (i = i - 1; i >= 0; i--)
			if (test_bit(i, indio_dev->active_scan_mask))
				sx9500_dec_chan_users(data, i);

	mutex_unlock(&data->mutex);

	return ret;
}