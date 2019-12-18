#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct input_handle {struct evdev* private; } ;
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct evdev {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  evdev_cleanup (struct evdev*) ; 
 int /*<<< orphan*/  input_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static void evdev_disconnect(struct input_handle *handle)
{
	struct evdev *evdev = handle->private;

	cdev_device_del(&evdev->cdev, &evdev->dev);
	evdev_cleanup(evdev);
	input_free_minor(MINOR(evdev->dev.devt));
	input_unregister_handle(handle);
	put_device(&evdev->dev);
}