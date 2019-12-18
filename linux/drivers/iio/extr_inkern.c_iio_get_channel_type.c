#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_channel {TYPE_2__* indio_dev; TYPE_1__* channel; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;
struct TYPE_4__ {int /*<<< orphan*/  info_exist_lock; int /*<<< orphan*/ * info; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_get_channel_type(struct iio_channel *chan, enum iio_chan_type *type)
{
	int ret = 0;
	/* Need to verify underlying driver has not gone away */

	mutex_lock(&chan->indio_dev->info_exist_lock);
	if (chan->indio_dev->info == NULL) {
		ret = -ENODEV;
		goto err_unlock;
	}

	*type = chan->channel->type;
err_unlock:
	mutex_unlock(&chan->indio_dev->info_exist_lock);

	return ret;
}