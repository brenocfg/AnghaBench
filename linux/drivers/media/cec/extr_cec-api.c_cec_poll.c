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
struct file {struct cec_fh* private_data; } ;
struct cec_fh {scalar_t__ total_queued_events; scalar_t__ queued_msgs; int /*<<< orphan*/  wait; struct cec_adapter* adap; } ;
struct cec_adapter {scalar_t__ transmit_queue_sz; int /*<<< orphan*/  lock; scalar_t__ is_configured; } ;
typedef  int __poll_t ;

/* Variables and functions */
 scalar_t__ CEC_MAX_MSG_TX_QUEUE_SZ ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  cec_is_registered (struct cec_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t cec_poll(struct file *filp,
			     struct poll_table_struct *poll)
{
	struct cec_fh *fh = filp->private_data;
	struct cec_adapter *adap = fh->adap;
	__poll_t res = 0;

	poll_wait(filp, &fh->wait, poll);
	if (!cec_is_registered(adap))
		return EPOLLERR | EPOLLHUP;
	mutex_lock(&adap->lock);
	if (adap->is_configured &&
	    adap->transmit_queue_sz < CEC_MAX_MSG_TX_QUEUE_SZ)
		res |= EPOLLOUT | EPOLLWRNORM;
	if (fh->queued_msgs)
		res |= EPOLLIN | EPOLLRDNORM;
	if (fh->total_queued_events)
		res |= EPOLLPRI;
	mutex_unlock(&adap->lock);
	return res;
}