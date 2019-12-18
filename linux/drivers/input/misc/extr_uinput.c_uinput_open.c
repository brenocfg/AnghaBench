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
struct uinput_device {int /*<<< orphan*/  state; int /*<<< orphan*/  waitq; int /*<<< orphan*/  requests_waitq; int /*<<< orphan*/  requests_lock; int /*<<< orphan*/  mutex; } ;
struct inode {int dummy; } ;
struct file {struct uinput_device* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UIST_NEW_DEVICE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct uinput_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int uinput_open(struct inode *inode, struct file *file)
{
	struct uinput_device *newdev;

	newdev = kzalloc(sizeof(struct uinput_device), GFP_KERNEL);
	if (!newdev)
		return -ENOMEM;

	mutex_init(&newdev->mutex);
	spin_lock_init(&newdev->requests_lock);
	init_waitqueue_head(&newdev->requests_waitq);
	init_waitqueue_head(&newdev->waitq);
	newdev->state = UIST_NEW_DEVICE;

	file->private_data = newdev;
	stream_open(inode, file);

	return 0;
}