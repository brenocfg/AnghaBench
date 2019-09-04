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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct ipoib_dev_priv {TYPE_1__ ah_reap_task; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_reap_ah (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_flush_ah(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	cancel_delayed_work(&priv->ah_reap_task);
	flush_workqueue(priv->wq);
	ipoib_reap_ah(&priv->ah_reap_task.work);
}