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
struct file {struct evdev_client* private_data; } ;
struct evdev_client {int /*<<< orphan*/  revoked; struct evdev* evdev; } ;
struct evdev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  handle; scalar_t__ exist; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  input_flush_device (int /*<<< orphan*/ *,struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_flush(struct file *file, fl_owner_t id)
{
	struct evdev_client *client = file->private_data;
	struct evdev *evdev = client->evdev;

	mutex_lock(&evdev->mutex);

	if (evdev->exist && !client->revoked)
		input_flush_device(&evdev->handle, file);

	mutex_unlock(&evdev->mutex);
	return 0;
}