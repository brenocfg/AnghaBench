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
struct input_handle {int /*<<< orphan*/  open; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  (* close ) (struct input_dev*) ;scalar_t__ poller; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  __input_release_device (struct input_handle*) ; 
 int /*<<< orphan*/  input_dev_poller_stop (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct input_dev*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void input_close_device(struct input_handle *handle)
{
	struct input_dev *dev = handle->dev;

	mutex_lock(&dev->mutex);

	__input_release_device(handle);

	if (!--dev->users) {
		if (dev->poller)
			input_dev_poller_stop(dev->poller);

		if (dev->close)
			dev->close(dev);
	}

	if (!--handle->open) {
		/*
		 * synchronize_rcu() makes sure that input_pass_event()
		 * completed and that no more input events are delivered
		 * through this handle
		 */
		synchronize_rcu();
	}

	mutex_unlock(&dev->mutex);
}