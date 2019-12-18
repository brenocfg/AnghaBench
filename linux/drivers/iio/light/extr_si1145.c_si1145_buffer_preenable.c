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
struct si1145_data {int /*<<< orphan*/  lock; } ;
struct iio_dev {int /*<<< orphan*/ * active_scan_mask; } ;

/* Variables and functions */
 struct si1145_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si1145_set_chlist (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1145_buffer_preenable(struct iio_dev *indio_dev)
{
	struct si1145_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->lock);
	ret = si1145_set_chlist(indio_dev, *indio_dev->active_scan_mask);
	mutex_unlock(&data->lock);

	return ret;
}