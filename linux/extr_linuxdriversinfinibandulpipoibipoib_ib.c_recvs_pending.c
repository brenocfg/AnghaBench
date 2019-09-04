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
struct ipoib_dev_priv {TYPE_1__* rx_ring; } ;
struct TYPE_2__ {scalar_t__ skb; } ;

/* Variables and functions */
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int ipoib_recvq_size ; 

__attribute__((used)) static int recvs_pending(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int pending = 0;
	int i;

	for (i = 0; i < ipoib_recvq_size; ++i)
		if (priv->rx_ring[i].skb)
			++pending;

	return pending;
}