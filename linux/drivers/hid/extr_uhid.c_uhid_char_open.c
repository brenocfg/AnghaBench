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
struct uhid_device {int running; int /*<<< orphan*/  worker; int /*<<< orphan*/  report_wait; int /*<<< orphan*/  waitq; int /*<<< orphan*/  qlock; int /*<<< orphan*/  report_lock; int /*<<< orphan*/  devlock; } ;
struct inode {int dummy; } ;
struct file {struct uhid_device* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct uhid_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  uhid_device_add_worker ; 

__attribute__((used)) static int uhid_char_open(struct inode *inode, struct file *file)
{
	struct uhid_device *uhid;

	uhid = kzalloc(sizeof(*uhid), GFP_KERNEL);
	if (!uhid)
		return -ENOMEM;

	mutex_init(&uhid->devlock);
	mutex_init(&uhid->report_lock);
	spin_lock_init(&uhid->qlock);
	init_waitqueue_head(&uhid->waitq);
	init_waitqueue_head(&uhid->report_wait);
	uhid->running = false;
	INIT_WORK(&uhid->worker, uhid_device_add_worker);

	file->private_data = uhid;
	stream_open(inode, file);

	return 0;
}