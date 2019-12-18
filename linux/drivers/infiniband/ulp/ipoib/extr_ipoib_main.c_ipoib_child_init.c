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
struct ipoib_dev_priv {int /*<<< orphan*/  local_gid; TYPE_1__* dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_ib_mtu; struct net_device* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int INFINIBAND_ALEN ; 
 int /*<<< orphan*/  IPOIB_FLAG_SUBINTERFACE ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_child_init(struct net_device *ndev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(ndev);
	struct ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

	priv->max_ib_mtu = ppriv->max_ib_mtu;
	set_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags);
	memcpy(priv->dev->dev_addr, ppriv->dev->dev_addr, INFINIBAND_ALEN);
	memcpy(&priv->local_gid, &ppriv->local_gid, sizeof(priv->local_gid));
}