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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  mcast_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 

int ipoib_mcast_stop_thread(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg_mcast(priv, "stopping multicast thread\n");

	cancel_delayed_work_sync(&priv->mcast_task);

	return 0;
}