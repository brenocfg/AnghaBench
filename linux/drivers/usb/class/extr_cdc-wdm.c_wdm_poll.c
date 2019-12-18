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
struct wdm_device {int /*<<< orphan*/  wait; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  flags; scalar_t__ werr; scalar_t__ rerr; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct wdm_device* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  WDM_DISCONNECTING ; 
 int /*<<< orphan*/  WDM_IN_USE ; 
 int /*<<< orphan*/  WDM_READ ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t wdm_poll(struct file *file, struct poll_table_struct *wait)
{
	struct wdm_device *desc = file->private_data;
	unsigned long flags;
	__poll_t mask = 0;

	spin_lock_irqsave(&desc->iuspin, flags);
	if (test_bit(WDM_DISCONNECTING, &desc->flags)) {
		mask = EPOLLHUP | EPOLLERR;
		spin_unlock_irqrestore(&desc->iuspin, flags);
		goto desc_out;
	}
	if (test_bit(WDM_READ, &desc->flags))
		mask = EPOLLIN | EPOLLRDNORM;
	if (desc->rerr || desc->werr)
		mask |= EPOLLERR;
	if (!test_bit(WDM_IN_USE, &desc->flags))
		mask |= EPOLLOUT | EPOLLWRNORM;
	spin_unlock_irqrestore(&desc->iuspin, flags);

	poll_wait(file, &desc->wait, wait);

desc_out:
	return mask;
}