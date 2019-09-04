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
struct reader_dev {int /*<<< orphan*/  buffer_status; int /*<<< orphan*/  poll_wait; } ;
struct file {struct reader_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_READABLE ; 
 int /*<<< orphan*/  BS_WRITABLE ; 
 int /*<<< orphan*/  DEBUGP (int,struct reader_dev*,char*,int) ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t cm4040_poll(struct file *filp, poll_table *wait)
{
	struct reader_dev *dev = filp->private_data;
	__poll_t mask = 0;

	poll_wait(filp, &dev->poll_wait, wait);

	if (test_and_clear_bit(BS_READABLE, &dev->buffer_status))
		mask |= EPOLLIN | EPOLLRDNORM;
	if (test_and_clear_bit(BS_WRITABLE, &dev->buffer_status))
		mask |= EPOLLOUT | EPOLLWRNORM;

	DEBUGP(2, dev, "<- cm4040_poll(%u)\n", mask);

	return mask;
}