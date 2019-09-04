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
struct file {int dummy; } ;
struct bsg_device {int dummy; } ;
struct bsg_class_device {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct bsg_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct bsg_device* __bsg_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bsg_device* bsg_add_device (struct inode*,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  bsg_minor_idr ; 
 int /*<<< orphan*/  bsg_mutex ; 
 struct bsg_class_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bsg_device *bsg_get_device(struct inode *inode, struct file *file)
{
	struct bsg_device *bd;
	struct bsg_class_device *bcd;

	/*
	 * find the class device
	 */
	mutex_lock(&bsg_mutex);
	bcd = idr_find(&bsg_minor_idr, iminor(inode));

	if (!bcd) {
		bd = ERR_PTR(-ENODEV);
		goto out_unlock;
	}

	bd = __bsg_get_device(iminor(inode), bcd->queue);
	if (!bd)
		bd = bsg_add_device(inode, bcd->queue, file);

out_unlock:
	mutex_unlock(&bsg_mutex);
	return bd;
}