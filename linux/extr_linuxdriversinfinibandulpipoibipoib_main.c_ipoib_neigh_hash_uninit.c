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
struct TYPE_2__ {int /*<<< orphan*/  deleted; } ;
struct ipoib_dev_priv {TYPE_1__ ntbl; int /*<<< orphan*/  neigh_reap_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_flush_neighs (struct ipoib_dev_priv*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_neigh_hash_uninit(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "ipoib_neigh_hash_uninit\n");
	init_completion(&priv->ntbl.deleted);

	cancel_delayed_work_sync(&priv->neigh_reap_task);

	ipoib_flush_neighs(priv);

	wait_for_completion(&priv->ntbl.deleted);
}