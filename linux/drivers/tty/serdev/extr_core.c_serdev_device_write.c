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
struct serdev_device {int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_comp; TYPE_1__* ops; struct serdev_controller* ctrl; } ;
struct serdev_controller {TYPE_2__* ops; } ;
struct TYPE_4__ {int (* write_buf ) (struct serdev_controller*,unsigned char const*,size_t) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  write_wakeup; } ;

/* Variables and functions */
 int EINVAL ; 
 long ERESTARTSYS ; 
 int ETIMEDOUT ; 
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct serdev_controller*,unsigned char const*,size_t) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,long) ; 

int serdev_device_write(struct serdev_device *serdev,
			const unsigned char *buf, size_t count,
			long timeout)
{
	struct serdev_controller *ctrl = serdev->ctrl;
	int written = 0;
	int ret;

	if (!ctrl || !ctrl->ops->write_buf || !serdev->ops->write_wakeup)
		return -EINVAL;

	if (timeout == 0)
		timeout = MAX_SCHEDULE_TIMEOUT;

	mutex_lock(&serdev->write_lock);
	do {
		reinit_completion(&serdev->write_comp);

		ret = ctrl->ops->write_buf(ctrl, buf, count);
		if (ret < 0)
			break;

		written += ret;
		buf += ret;
		count -= ret;

		if (count == 0)
			break;

		timeout = wait_for_completion_interruptible_timeout(&serdev->write_comp,
								    timeout);
	} while (timeout > 0);
	mutex_unlock(&serdev->write_lock);

	if (ret < 0)
		return ret;

	if (timeout <= 0 && written == 0) {
		if (timeout == -ERESTARTSYS)
			return -ERESTARTSYS;
		else
			return -ETIMEDOUT;
	}

	return written;
}