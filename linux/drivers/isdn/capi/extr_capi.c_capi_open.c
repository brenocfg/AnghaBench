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
struct inode {int dummy; } ;
struct file {struct capidev* private_data; } ;
struct capidev {int /*<<< orphan*/  list; int /*<<< orphan*/  nccis; int /*<<< orphan*/  recvwait; int /*<<< orphan*/  recvqueue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capidev_list ; 
 int /*<<< orphan*/  capidev_list_lock ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct capidev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int capi_open(struct inode *inode, struct file *file)
{
	struct capidev *cdev;

	cdev = kzalloc(sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return -ENOMEM;

	mutex_init(&cdev->lock);
	skb_queue_head_init(&cdev->recvqueue);
	init_waitqueue_head(&cdev->recvwait);
	INIT_LIST_HEAD(&cdev->nccis);
	file->private_data = cdev;

	mutex_lock(&capidev_list_lock);
	list_add_tail(&cdev->list, &capidev_list);
	mutex_unlock(&capidev_list_lock);

	return stream_open(inode, file);
}