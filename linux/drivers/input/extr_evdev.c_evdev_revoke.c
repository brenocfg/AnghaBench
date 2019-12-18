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
struct file {int dummy; } ;
struct evdev_client {int revoked; } ;
struct evdev {int /*<<< orphan*/  wait; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  evdev_ungrab (struct evdev*,struct evdev_client*) ; 
 int /*<<< orphan*/  input_flush_device (int /*<<< orphan*/ *,struct file*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evdev_revoke(struct evdev *evdev, struct evdev_client *client,
			struct file *file)
{
	client->revoked = true;
	evdev_ungrab(evdev, client);
	input_flush_device(&evdev->handle, file);
	wake_up_interruptible(&evdev->wait);

	return 0;
}