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
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct file {int dummy; } ;
struct comp_channel {int /*<<< orphan*/  io_mutex; scalar_t__ dev; int /*<<< orphan*/  unlink; scalar_t__ access_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_channel (struct comp_channel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_channel (struct comp_channel*) ; 
 struct comp_channel* to_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comp_close(struct inode *inode, struct file *filp)
{
	struct comp_channel *c = to_channel(inode->i_cdev);

	mutex_lock(&c->io_mutex);
	spin_lock(&c->unlink);
	c->access_ref = 0;
	spin_unlock(&c->unlink);
	if (c->dev) {
		stop_channel(c);
		mutex_unlock(&c->io_mutex);
	} else {
		mutex_unlock(&c->io_mutex);
		destroy_channel(c);
	}
	return 0;
}