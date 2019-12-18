#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {struct ep_data* i_private; } ;
struct file {struct ep_data* private_data; } ;
struct ep_data {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int EBUSY ; 
 int EINTR ; 
 int ENOENT ; 
 scalar_t__ STATE_DEV_UNBOUND ; 
 scalar_t__ STATE_EP_DISABLED ; 
 scalar_t__ STATE_EP_READY ; 
 int /*<<< orphan*/  VDEBUG (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ep (struct ep_data*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ep_open (struct inode *inode, struct file *fd)
{
	struct ep_data		*data = inode->i_private;
	int			value = -EBUSY;

	if (mutex_lock_interruptible(&data->lock) != 0)
		return -EINTR;
	spin_lock_irq (&data->dev->lock);
	if (data->dev->state == STATE_DEV_UNBOUND)
		value = -ENOENT;
	else if (data->state == STATE_EP_DISABLED) {
		value = 0;
		data->state = STATE_EP_READY;
		get_ep (data);
		fd->private_data = data;
		VDEBUG (data->dev, "%s ready\n", data->name);
	} else
		DBG (data->dev, "%s state %d\n",
			data->name, data->state);
	spin_unlock_irq (&data->dev->lock);
	mutex_unlock(&data->lock);
	return value;
}