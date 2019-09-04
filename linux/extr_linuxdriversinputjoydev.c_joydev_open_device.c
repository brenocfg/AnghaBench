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
struct joydev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  open; int /*<<< orphan*/  handle; int /*<<< orphan*/  exist; } ;

/* Variables and functions */
 int ENODEV ; 
 int input_open_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  joydev_refresh_state (struct joydev*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int joydev_open_device(struct joydev *joydev)
{
	int retval;

	retval = mutex_lock_interruptible(&joydev->mutex);
	if (retval)
		return retval;

	if (!joydev->exist)
		retval = -ENODEV;
	else if (!joydev->open++) {
		retval = input_open_device(&joydev->handle);
		if (retval)
			joydev->open--;
		else
			joydev_refresh_state(joydev);
	}

	mutex_unlock(&joydev->mutex);
	return retval;
}