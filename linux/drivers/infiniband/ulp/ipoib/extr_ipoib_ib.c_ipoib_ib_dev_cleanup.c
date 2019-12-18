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
struct ipoib_dev_priv {int /*<<< orphan*/ * pd; TYPE_1__* rn_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_uninit ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_flush_paths (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_dev_flush (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_stop_thread (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_stop_ah (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

void ipoib_ib_dev_cleanup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "cleaning up ib_dev\n");
	/*
	 * We must make sure there are no more (path) completions
	 * that may wish to touch priv fields that are no longer valid
	 */
	ipoib_flush_paths(dev);

	ipoib_mcast_stop_thread(dev);
	ipoib_mcast_dev_flush(dev);

	/*
	 * All of our ah references aren't free until after
	 * ipoib_mcast_dev_flush(), ipoib_flush_paths, and
	 * the neighbor garbage collection is stopped and reaped.
	 * That should all be done now, so make a final ah flush.
	 */
	ipoib_stop_ah(dev);

	clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);

	priv->rn_ops->ndo_uninit(dev);

	if (priv->pd) {
		ib_dealloc_pd(priv->pd);
		priv->pd = NULL;
	}
}