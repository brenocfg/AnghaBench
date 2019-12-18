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
struct kxsd9_state {int /*<<< orphan*/  dev; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_SCALE ; 
 struct kxsd9_state* iio_priv (struct iio_dev*) ; 
 int kxsd9_write_scale (struct iio_dev*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kxsd9_write_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int val,
			   int val2,
			   long mask)
{
	int ret = -EINVAL;
	struct kxsd9_state *st = iio_priv(indio_dev);

	pm_runtime_get_sync(st->dev);

	if (mask == IIO_CHAN_INFO_SCALE) {
		/* Check no integer component */
		if (val)
			return -EINVAL;
		ret = kxsd9_write_scale(indio_dev, val2);
	}

	pm_runtime_mark_last_busy(st->dev);
	pm_runtime_put_autosuspend(st->dev);

	return ret;
}