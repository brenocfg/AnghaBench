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
struct iio_dev {int /*<<< orphan*/  info_exist_lock; int /*<<< orphan*/  mlock; int /*<<< orphan*/ * info; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int __iio_update_buffers (struct iio_dev*,struct iio_buffer*,struct iio_buffer*) ; 
 scalar_t__ iio_buffer_is_active (struct iio_buffer*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iio_update_buffers(struct iio_dev *indio_dev,
		       struct iio_buffer *insert_buffer,
		       struct iio_buffer *remove_buffer)
{
	int ret;

	if (insert_buffer == remove_buffer)
		return 0;

	mutex_lock(&indio_dev->info_exist_lock);
	mutex_lock(&indio_dev->mlock);

	if (insert_buffer && iio_buffer_is_active(insert_buffer))
		insert_buffer = NULL;

	if (remove_buffer && !iio_buffer_is_active(remove_buffer))
		remove_buffer = NULL;

	if (!insert_buffer && !remove_buffer) {
		ret = 0;
		goto out_unlock;
	}

	if (indio_dev->info == NULL) {
		ret = -ENODEV;
		goto out_unlock;
	}

	ret = __iio_update_buffers(indio_dev, insert_buffer, remove_buffer);

out_unlock:
	mutex_unlock(&indio_dev->mlock);
	mutex_unlock(&indio_dev->info_exist_lock);

	return ret;
}