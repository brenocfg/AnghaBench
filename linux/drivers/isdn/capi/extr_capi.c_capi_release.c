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
struct inode {int dummy; } ;
struct file {struct capidev* private_data; } ;
struct TYPE_2__ {scalar_t__ applid; } ;
struct capidev {int /*<<< orphan*/  recvqueue; TYPE_1__ ap; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  capi20_release (TYPE_1__*) ; 
 int /*<<< orphan*/  capidev_list_lock ; 
 int /*<<< orphan*/  capincci_free (struct capidev*,int) ; 
 int /*<<< orphan*/  kfree (struct capidev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int capi_release(struct inode *inode, struct file *file)
{
	struct capidev *cdev = file->private_data;

	mutex_lock(&capidev_list_lock);
	list_del(&cdev->list);
	mutex_unlock(&capidev_list_lock);

	if (cdev->ap.applid)
		capi20_release(&cdev->ap);
	skb_queue_purge(&cdev->recvqueue);
	capincci_free(cdev, 0xffffffff);

	kfree(cdev);
	return 0;
}