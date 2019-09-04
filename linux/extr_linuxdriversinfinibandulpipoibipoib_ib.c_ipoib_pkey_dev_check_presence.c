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
struct rdma_netdev {int /*<<< orphan*/  (* set_id ) (struct net_device*,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int pkey; int /*<<< orphan*/  flags; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ib_find_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ) ; 

void ipoib_pkey_dev_check_presence(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct rdma_netdev *rn = netdev_priv(dev);

	if (!(priv->pkey & 0x7fff) ||
	    ib_find_pkey(priv->ca, priv->port, priv->pkey,
			 &priv->pkey_index)) {
		clear_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
	} else {
		if (rn->set_id)
			rn->set_id(dev, priv->pkey_index);
		set_bit(IPOIB_PKEY_ASSIGNED, &priv->flags);
	}
}