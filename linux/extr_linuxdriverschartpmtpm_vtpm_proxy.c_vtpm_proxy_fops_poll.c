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
struct proxy_dev {int state; int /*<<< orphan*/  buf_lock; scalar_t__ req_len; int /*<<< orphan*/  wq; } ;
struct file {struct proxy_dev* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int STATE_OPENED_FLAG ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t vtpm_proxy_fops_poll(struct file *filp, poll_table *wait)
{
	struct proxy_dev *proxy_dev = filp->private_data;
	__poll_t ret;

	poll_wait(filp, &proxy_dev->wq, wait);

	ret = EPOLLOUT;

	mutex_lock(&proxy_dev->buf_lock);

	if (proxy_dev->req_len)
		ret |= EPOLLIN | EPOLLRDNORM;

	if (!(proxy_dev->state & STATE_OPENED_FLAG))
		ret |= EPOLLHUP;

	mutex_unlock(&proxy_dev->buf_lock);

	return ret;
}