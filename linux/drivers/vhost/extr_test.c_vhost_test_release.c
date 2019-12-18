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
struct vhost_test {int /*<<< orphan*/  dev; } ;
struct inode {int dummy; } ;
struct file {struct vhost_test* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vhost_test*) ; 
 int /*<<< orphan*/  vhost_dev_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_dev_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_test_flush (struct vhost_test*) ; 
 int /*<<< orphan*/  vhost_test_stop (struct vhost_test*,void**) ; 

__attribute__((used)) static int vhost_test_release(struct inode *inode, struct file *f)
{
	struct vhost_test *n = f->private_data;
	void  *private;

	vhost_test_stop(n, &private);
	vhost_test_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_cleanup(&n->dev);
	/* We do an extra flush before freeing memory,
	 * since jobs can re-queue themselves. */
	vhost_test_flush(n);
	kfree(n);
	return 0;
}