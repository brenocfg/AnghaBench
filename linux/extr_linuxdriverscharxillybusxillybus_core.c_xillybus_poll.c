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
struct xilly_channel {TYPE_1__* endpoint; int /*<<< orphan*/  rd_spinlock; int /*<<< orphan*/  rd_full; int /*<<< orphan*/  rd_wait; scalar_t__ rd_allow_partial; int /*<<< orphan*/  wr_spinlock; scalar_t__ wr_hangup; scalar_t__ wr_ready; int /*<<< orphan*/  wr_empty; int /*<<< orphan*/  wr_ready_wait; int /*<<< orphan*/  wr_wait; scalar_t__ wr_supports_nonempty; int /*<<< orphan*/  wr_synchronous; } ;
struct file {struct xilly_channel* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {scalar_t__ fatal_error; int /*<<< orphan*/  ep_wait; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static __poll_t xillybus_poll(struct file *filp, poll_table *wait)
{
	struct xilly_channel *channel = filp->private_data;
	__poll_t mask = 0;
	unsigned long flags;

	poll_wait(filp, &channel->endpoint->ep_wait, wait);

	/*
	 * poll() won't play ball regarding read() channels which
	 * aren't asynchronous and support the nonempty message. Allowing
	 * that will create situations where data has been delivered at
	 * the FPGA, and users expecting select() to wake up, which it may
	 * not.
	 */

	if (!channel->wr_synchronous && channel->wr_supports_nonempty) {
		poll_wait(filp, &channel->wr_wait, wait);
		poll_wait(filp, &channel->wr_ready_wait, wait);

		spin_lock_irqsave(&channel->wr_spinlock, flags);
		if (!channel->wr_empty || channel->wr_ready)
			mask |= EPOLLIN | EPOLLRDNORM;

		if (channel->wr_hangup)
			/*
			 * Not EPOLLHUP, because its behavior is in the
			 * mist, and EPOLLIN does what we want: Wake up
			 * the read file descriptor so it sees EOF.
			 */
			mask |=  EPOLLIN | EPOLLRDNORM;
		spin_unlock_irqrestore(&channel->wr_spinlock, flags);
	}

	/*
	 * If partial data write is disallowed on a write() channel,
	 * it's pointless to ever signal OK to write, because is could
	 * block despite some space being available.
	 */

	if (channel->rd_allow_partial) {
		poll_wait(filp, &channel->rd_wait, wait);

		spin_lock_irqsave(&channel->rd_spinlock, flags);
		if (!channel->rd_full)
			mask |= EPOLLOUT | EPOLLWRNORM;
		spin_unlock_irqrestore(&channel->rd_spinlock, flags);
	}

	if (channel->endpoint->fatal_error)
		mask |= EPOLLERR;

	return mask;
}