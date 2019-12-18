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
struct ipoib_dev_priv {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_flush_paths (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_dev_flush (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_mcast_stop_thread (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 

void ipoib_ib_dev_down(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg(priv, "downing ib_dev\n");

	clear_bit(IPOIB_FLAG_OPER_UP, &priv->flags);
	netif_carrier_off(dev);

	ipoib_mcast_stop_thread(dev);
	ipoib_mcast_dev_flush(dev);

	ipoib_flush_paths(dev);
}