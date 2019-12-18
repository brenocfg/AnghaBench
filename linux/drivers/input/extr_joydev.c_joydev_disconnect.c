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
struct TYPE_3__ {int /*<<< orphan*/  devt; } ;
struct joydev {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;
struct input_handle {struct joydev* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  input_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_handle (struct input_handle*) ; 
 int /*<<< orphan*/  joydev_cleanup (struct joydev*) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 

__attribute__((used)) static void joydev_disconnect(struct input_handle *handle)
{
	struct joydev *joydev = handle->private;

	cdev_device_del(&joydev->cdev, &joydev->dev);
	joydev_cleanup(joydev);
	input_free_minor(MINOR(joydev->dev.devt));
	input_unregister_handle(handle);
	put_device(&joydev->dev);
}