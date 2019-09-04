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
struct nfeth_private {int /*<<< orphan*/  ethX; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ XIF_STOP ; 
 struct nfeth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ nfEtherID ; 
 int /*<<< orphan*/  nf_call (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfeth_stop(struct net_device *dev)
{
	struct nfeth_private *priv = netdev_priv(dev);

	/* No more data */
	netif_stop_queue(dev);

	nf_call(nfEtherID + XIF_STOP, priv->ethX);

	return 0;
}