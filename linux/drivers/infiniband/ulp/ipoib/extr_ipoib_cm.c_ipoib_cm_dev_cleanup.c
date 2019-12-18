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
struct TYPE_2__ {int /*<<< orphan*/ * srq_ring; int /*<<< orphan*/ * srq; } ;
struct ipoib_dev_priv {TYPE_1__ cm; } ;

/* Variables and functions */
 int ib_destroy_srq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_cm_free_rx_ring (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 

void ipoib_cm_dev_cleanup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret;

	if (!priv->cm.srq)
		return;

	ipoib_dbg(priv, "Cleanup ipoib connected mode.\n");

	ret = ib_destroy_srq(priv->cm.srq);
	if (ret)
		ipoib_warn(priv, "ib_destroy_srq failed: %d\n", ret);

	priv->cm.srq = NULL;
	if (!priv->cm.srq_ring)
		return;

	ipoib_cm_free_rx_ring(dev, priv->cm.srq_ring);
	priv->cm.srq_ring = NULL;
}