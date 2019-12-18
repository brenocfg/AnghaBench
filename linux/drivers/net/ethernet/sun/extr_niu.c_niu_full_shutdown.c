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
struct niu {int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  reset_task; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  niu_disable_napi (struct niu*) ; 
 int /*<<< orphan*/  niu_stop_hw (struct niu*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void niu_full_shutdown(struct niu *np, struct net_device *dev)
{
	cancel_work_sync(&np->reset_task);

	niu_disable_napi(np);
	netif_tx_stop_all_queues(dev);

	del_timer_sync(&np->timer);

	spin_lock_irq(&np->lock);

	niu_stop_hw(np);

	spin_unlock_irq(&np->lock);
}