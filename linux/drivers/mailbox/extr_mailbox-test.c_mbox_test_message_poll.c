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
struct poll_table_struct {int dummy; } ;
struct mbox_test_device {int /*<<< orphan*/  waitq; } ;
struct file {struct mbox_test_device* private_data; } ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 scalar_t__ mbox_test_message_data_ready (struct mbox_test_device*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t
mbox_test_message_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct mbox_test_device *tdev = filp->private_data;

	poll_wait(filp, &tdev->waitq, wait);

	if (mbox_test_message_data_ready(tdev))
		return EPOLLIN | EPOLLRDNORM;
	return 0;
}