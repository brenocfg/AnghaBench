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
struct iio_channel {TYPE_1__* indio_dev; } ;
typedef  enum iio_chan_info_enum { ____Placeholder_iio_chan_info_enum } iio_chan_info_enum ;
struct TYPE_2__ {int /*<<< orphan*/  info_exist_lock; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int ENODEV ; 
 int iio_channel_read_avail (struct iio_channel*,int const**,int*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_read_avail_channel_attribute(struct iio_channel *chan,
				     const int **vals, int *type, int *length,
				     enum iio_chan_info_enum attribute)
{
	int ret;

	mutex_lock(&chan->indio_dev->info_exist_lock);
	if (!chan->indio_dev->info) {
		ret = -ENODEV;
		goto err_unlock;
	}

	ret = iio_channel_read_avail(chan, vals, type, length, attribute);
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	return ret;
}