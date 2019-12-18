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
struct tb {int /*<<< orphan*/  dev; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctl; TYPE_1__* cm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop ) (struct tb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tb*) ; 
 int /*<<< orphan*/  tb_ctl_stop (int /*<<< orphan*/ ) ; 

void tb_domain_remove(struct tb *tb)
{
	mutex_lock(&tb->lock);
	if (tb->cm_ops->stop)
		tb->cm_ops->stop(tb);
	/* Stop the domain control traffic */
	tb_ctl_stop(tb->ctl);
	mutex_unlock(&tb->lock);

	flush_workqueue(tb->wq);
	device_unregister(&tb->dev);
}