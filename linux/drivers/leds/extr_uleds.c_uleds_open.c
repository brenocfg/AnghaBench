#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct uleds_device {int /*<<< orphan*/  state; int /*<<< orphan*/  waitq; int /*<<< orphan*/  mutex; TYPE_2__ led_cdev; TYPE_1__ user_dev; } ;
struct inode {int dummy; } ;
struct file {struct uleds_device* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ULEDS_STATE_UNKNOWN ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct uleds_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  uleds_brightness_set ; 

__attribute__((used)) static int uleds_open(struct inode *inode, struct file *file)
{
	struct uleds_device *udev;

	udev = kzalloc(sizeof(*udev), GFP_KERNEL);
	if (!udev)
		return -ENOMEM;

	udev->led_cdev.name = udev->user_dev.name;
	udev->led_cdev.brightness_set = uleds_brightness_set;

	mutex_init(&udev->mutex);
	init_waitqueue_head(&udev->waitq);
	udev->state = ULEDS_STATE_UNKNOWN;

	file->private_data = udev;
	stream_open(inode, file);

	return 0;
}