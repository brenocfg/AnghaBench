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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  event_handler; TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  dev_change_flags (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void ipoib_parent_unregister_pre(struct net_device *ndev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(ndev);

	/*
	 * ipoib_set_mac checks netif_running before pushing work, clearing
	 * running ensures the it will not add more work.
	 */
	rtnl_lock();
	dev_change_flags(priv->dev, priv->dev->flags & ~IFF_UP, NULL);
	rtnl_unlock();

	/* ipoib_event() cannot be running once this returns */
	ib_unregister_event_handler(&priv->event_handler);

	/*
	 * Work on the queue grabs the rtnl lock, so this cannot be done while
	 * also holding it.
	 */
	flush_workqueue(ipoib_workqueue);
}