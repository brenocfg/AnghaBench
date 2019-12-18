#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uleds_device {scalar_t__ state; int /*<<< orphan*/  led_cdev; } ;
struct inode {int dummy; } ;
struct file {struct uleds_device* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  this_device; } ;

/* Variables and functions */
 scalar_t__ ULEDS_STATE_REGISTERED ; 
 scalar_t__ ULEDS_STATE_UNKNOWN ; 
 int /*<<< orphan*/  devm_led_classdev_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uleds_device*) ; 
 TYPE_1__ uleds_misc ; 

__attribute__((used)) static int uleds_release(struct inode *inode, struct file *file)
{
	struct uleds_device *udev = file->private_data;

	if (udev->state == ULEDS_STATE_REGISTERED) {
		udev->state = ULEDS_STATE_UNKNOWN;
		devm_led_classdev_unregister(uleds_misc.this_device,
					     &udev->led_cdev);
	}
	kfree(udev);

	return 0;
}