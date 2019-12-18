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
struct file {struct comp_channel* private_data; } ;
struct comp_channel {int /*<<< orphan*/  io_mutex; int /*<<< orphan*/  fifo; int /*<<< orphan*/  dev; TYPE_1__* cfg; int /*<<< orphan*/  wq; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_2__ {scalar_t__ direction; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ MOST_CH_RX ; 
 scalar_t__ ch_has_mbo (struct comp_channel*) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t comp_poll(struct file *filp, poll_table *wait)
{
	struct comp_channel *c = filp->private_data;
	__poll_t mask = 0;

	poll_wait(filp, &c->wq, wait);

	mutex_lock(&c->io_mutex);
	if (c->cfg->direction == MOST_CH_RX) {
		if (!c->dev || !kfifo_is_empty(&c->fifo))
			mask |= EPOLLIN | EPOLLRDNORM;
	} else {
		if (!c->dev || !kfifo_is_empty(&c->fifo) || ch_has_mbo(c))
			mask |= EPOLLOUT | EPOLLWRNORM;
	}
	mutex_unlock(&c->io_mutex);
	return mask;
}