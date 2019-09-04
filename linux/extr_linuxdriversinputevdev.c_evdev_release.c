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
struct inode {int dummy; } ;
struct file {struct evdev_client* private_data; } ;
struct evdev_client {int /*<<< orphan*/ * evmasks; struct evdev* evdev; } ;
struct evdev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int EV_CNT ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_close_device (struct evdev*) ; 
 int /*<<< orphan*/  evdev_detach_client (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  evdev_ungrab (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  kvfree (struct evdev_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_release(struct inode *inode, struct file *file)
{
	struct evdev_client *client = file->private_data;
	struct evdev *evdev = client->evdev;
	unsigned int i;

	mutex_lock(&evdev->mutex);
	evdev_ungrab(evdev, client);
	mutex_unlock(&evdev->mutex);

	evdev_detach_client(evdev, client);

	for (i = 0; i < EV_CNT; ++i)
		bitmap_free(client->evmasks[i]);

	kvfree(client);

	evdev_close_device(evdev);

	return 0;
}