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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct scif_endpt {int /*<<< orphan*/  lock; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _scif_poll_wait(struct file *f, wait_queue_head_t *wq,
				   poll_table *p, struct scif_endpt *ep)
{
	/*
	 * Because poll_wait makes a GFP_KERNEL allocation, give up the lock
	 * and regrab it afterwards. Because the endpoint state might have
	 * changed while the lock was given up, the state must be checked
	 * again after re-acquiring the lock. The code in __scif_pollfd(..)
	 * does this.
	 */
	spin_unlock(&ep->lock);
	poll_wait(f, wq, p);
	spin_lock(&ep->lock);
}