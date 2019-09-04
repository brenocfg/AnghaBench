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
struct file {struct apm_user* private_data; } ;
struct apm_user {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  apm_waitqueue ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t apm_poll(struct file *fp, poll_table * wait)
{
	struct apm_user *as = fp->private_data;

	poll_wait(fp, &apm_waitqueue, wait);
	return queue_empty(&as->queue) ? 0 : EPOLLIN | EPOLLRDNORM;
}