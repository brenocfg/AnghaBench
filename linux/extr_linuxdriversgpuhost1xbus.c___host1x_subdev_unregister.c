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
struct host1x_subdev {int /*<<< orphan*/  list; struct host1x_client* client; } ;
struct host1x_device {int registered; int /*<<< orphan*/  clients_lock; int /*<<< orphan*/  subdevs; int /*<<< orphan*/  dev; } ;
struct host1x_client {int /*<<< orphan*/  list; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __host1x_subdev_unregister(struct host1x_device *device,
				       struct host1x_subdev *subdev)
{
	struct host1x_client *client = subdev->client;

	/*
	 * If all subdevices have been activated, we're about to remove the
	 * first active subdevice, so unload the driver first.
	 */
	if (list_empty(&device->subdevs)) {
		if (device->registered) {
			device->registered = false;
			device_del(&device->dev);
		}
	}

	/*
	 * Move the subdevice back to the list of idle subdevices and remove
	 * it from list of clients.
	 */
	mutex_lock(&device->clients_lock);
	subdev->client = NULL;
	client->parent = NULL;
	list_move_tail(&subdev->list, &device->subdevs);
	/*
	 * XXX: Perhaps don't do this here, but rather explicitly remove it
	 * when the device is about to be deleted.
	 *
	 * This is somewhat complicated by the fact that this function is
	 * used to remove the subdevice when a client is unregistered but
	 * also when the composite device is about to be removed.
	 */
	list_del_init(&client->list);
	mutex_unlock(&device->clients_lock);
}