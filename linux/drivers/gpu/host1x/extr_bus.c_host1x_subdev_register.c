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
struct host1x_subdev {struct host1x_client* client; int /*<<< orphan*/  list; } ;
struct host1x_device {int registered; int /*<<< orphan*/  dev; int /*<<< orphan*/  subdevs; int /*<<< orphan*/  subdevs_lock; int /*<<< orphan*/  clients_lock; int /*<<< orphan*/  active; int /*<<< orphan*/  clients; } ;
struct host1x_client {int /*<<< orphan*/ * parent; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void host1x_subdev_register(struct host1x_device *device,
				   struct host1x_subdev *subdev,
				   struct host1x_client *client)
{
	int err;

	/*
	 * Move the subdevice to the list of active (registered) subdevices
	 * and associate it with a client. At the same time, associate the
	 * client with its parent device.
	 */
	mutex_lock(&device->subdevs_lock);
	mutex_lock(&device->clients_lock);
	list_move_tail(&client->list, &device->clients);
	list_move_tail(&subdev->list, &device->active);
	client->parent = &device->dev;
	subdev->client = client;
	mutex_unlock(&device->clients_lock);
	mutex_unlock(&device->subdevs_lock);

	if (list_empty(&device->subdevs)) {
		err = device_add(&device->dev);
		if (err < 0)
			dev_err(&device->dev, "failed to add: %d\n", err);
		else
			device->registered = true;
	}
}