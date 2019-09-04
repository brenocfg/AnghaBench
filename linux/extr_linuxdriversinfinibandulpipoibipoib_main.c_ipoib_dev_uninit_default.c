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
struct ipoib_dev_priv {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipoib_cm_dev_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_napi_del (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_transport_dev_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_dev_uninit_default(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_transport_dev_cleanup(dev);

	ipoib_napi_del(dev);

	ipoib_cm_dev_cleanup(dev);

	kfree(priv->rx_ring);
	vfree(priv->tx_ring);

	priv->rx_ring = NULL;
	priv->tx_ring = NULL;
}