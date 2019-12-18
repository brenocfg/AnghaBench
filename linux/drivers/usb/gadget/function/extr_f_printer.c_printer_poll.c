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
struct printer_dev {int current_rx_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_buffers; int /*<<< orphan*/  tx_reqs; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_wait; int /*<<< orphan*/  lock_printer_io; } ;
struct file {struct printer_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_rx_reqs (struct printer_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t
printer_poll(struct file *fd, poll_table *wait)
{
	struct printer_dev	*dev = fd->private_data;
	unsigned long		flags;
	__poll_t		status = 0;

	mutex_lock(&dev->lock_printer_io);
	spin_lock_irqsave(&dev->lock, flags);
	setup_rx_reqs(dev);
	spin_unlock_irqrestore(&dev->lock, flags);
	mutex_unlock(&dev->lock_printer_io);

	poll_wait(fd, &dev->rx_wait, wait);
	poll_wait(fd, &dev->tx_wait, wait);

	spin_lock_irqsave(&dev->lock, flags);
	if (likely(!list_empty(&dev->tx_reqs)))
		status |= EPOLLOUT | EPOLLWRNORM;

	if (likely(dev->current_rx_bytes) ||
			likely(!list_empty(&dev->rx_buffers)))
		status |= EPOLLIN | EPOLLRDNORM;

	spin_unlock_irqrestore(&dev->lock, flags);

	return status;
}