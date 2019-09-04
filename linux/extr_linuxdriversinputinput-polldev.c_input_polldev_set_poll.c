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
struct input_polled_dev {unsigned int poll_interval_min; unsigned int poll_interval_max; unsigned int poll_interval; int /*<<< orphan*/  work; struct input_dev* input; } ;
struct input_dev {int /*<<< orphan*/  mutex; scalar_t__ users; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct input_polled_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  input_polldev_queue_work (struct input_polled_dev*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t input_polldev_set_poll(struct device *dev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
	struct input_polled_dev *polldev = dev_get_drvdata(dev);
	struct input_dev *input = polldev->input;
	unsigned int interval;
	int err;

	err = kstrtouint(buf, 0, &interval);
	if (err)
		return err;

	if (interval < polldev->poll_interval_min)
		return -EINVAL;

	if (interval > polldev->poll_interval_max)
		return -EINVAL;

	mutex_lock(&input->mutex);

	polldev->poll_interval = interval;

	if (input->users) {
		cancel_delayed_work_sync(&polldev->work);
		if (polldev->poll_interval > 0)
			input_polldev_queue_work(polldev);
	}

	mutex_unlock(&input->mutex);

	return count;
}